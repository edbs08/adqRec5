#include <QFile>
#include <QString>
#include <QTransform>
#include <QtGui>
#include <QKeyEvent>
#include <iostream>
#include "glwidget.h"

using namespace std;

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
     QWidget::setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

GLWidget::~GLWidget() {
}


void GLWidget::loadFaces(const QString &path) {
    string file_type = getFileExt(path);
    clear_variables();
    if(file_type == "json")
    {
        /*Implementation for json*/
        QFile json_file(path);
        if (!json_file.open(QIODevice::ReadOnly)) {
            qWarning("Failed to open file");
            exit(-1);
        }
        QByteArray json_data = json_file.readAll();
        QJsonDocument json_document(QJsonDocument::fromJson(json_data));
        face_collection.fromJson(json_document.array());
        face_collection.init=true;

    }

    else if(file_type == "stl")
    {
        QFile stl_file(path);
        if (!stl_file.open(QIODevice::ReadOnly)) {
            qWarning("Failed to open file");
            exit(-1);
        }
        face_collection.fromStl(path);
        face_collection.init=true;
    }

    else if(file_type == "pgm3d")
    {
        QFile pgm3D_file(path);
        if (!pgm3D_file.open(QIODevice::ReadOnly)) {
            qWarning("Failed to open file");
            exit(-1);
        }
        face_collection.frompgm3D(path);
        face_collection.init=true;
    }

    else if(file_type == "obj"){
        QFile obj_file(path);
        if (!obj_file.open(QIODevice::ReadOnly)) {
            qWarning("Failed to open file");
            exit(-1);
        }
        QByteArray obj_data = obj_file.readAll();
        face_collection.fromObj(path);
        face_collection.init=true;
    }

    else{
        std::cerr << "Invalid file type";
    }
    zoomScale = face_collection.init_scale;
    initializeGL();
}

string GLWidget::getFileExt(const QString& qs) {

   std::string s = qs.toLocal8Bit().constData();
   size_t i = s.rfind('.', s.length());
   if (i != string::npos) {
      return(s.substr(i+1, s.length() - i));
   }
   return("");
}

void GLWidget::clear_variables(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    zoomScale = 1;
    first_paint = true;

}
void GLWidget::initializeGL() {
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f); // Set background color
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    setMouseTracking(true);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_LIGHTING );
}

void GLWidget::paintGL() {
    makeCurrent();
    QSize viewport_size = size();
    glViewport(0, 0, viewport_size.width(), viewport_size.height());
    float ar = (float) viewport_size.width() / (float) viewport_size.height();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    /*Config Projection Matrix  GL_PROJECTION*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                 // Reset the model-view matrix
    /*Code for the aspect ratio*/
    if(viewport_size.width() <= viewport_size.height()){
        glOrtho(-1.0, 1.0, -1 / ar, 1.0 / ar, 1.0, -1.0);
    }
    else{
        glOrtho(-1.0 *ar, 1.0 *ar, -1.0, 1.0, 1.0, -1.0);
    }

    /*Config Model View Matrix  GL_MODELVIEW*/
    if (true == first_paint)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        first_paint = false;
    }
    else
    {
        glMatrixMode(GL_MODELVIEW);
        glGetFloatv(GL_MODELVIEW_MATRIX, m);
        glLoadIdentity();
        /*Rotation*/
        glRotatef(rotation_angle,rotation.y(),rotation.x(),0.0f);
        if(auto_rotation == true)
        {
            rotation_angle = 1;
            rotation.ry() = 0;
            rotation.rx() = 1;
            QWidget::update();
        }
        else
        {
            rotation_angle = 0;
        }
        /*Translation*/
        glTranslatef(translation.x(),translation.y(),0.0f);
        translation.rx()=0;
        translation.ry()=0;
        /*Scale*/
        glScalef(zoomScale, zoomScale, zoomScale);
        zoomScale = 1;

        glMultMatrixf(m);
        glGetFloatv(GL_MODELVIEW_MATRIX, m);

    }


  //*********** Draw the model//
  // Define vertices in counter-clockwise (CCW) order with normal pointing out
  QVector3D view_coords;
  vector<pair<float, int>> vp;
  double max_value = 0;

  if(sorting== SORTING_ON)
  {
      for (int face_index=0;face_index<face_collection.faces.size();face_index++)
      {
          Face face = face_collection.faces[face_index];
          view_coords = object2view(face, m);
          vp.push_back(make_pair(view_coords.z(), face_index));
      }
      sort(vp.begin(), vp.end());
      reverse(vp.begin(),vp.end());

  }
  if(face_collection.init==true)
  {
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glBlendEquation(GL_FUNC_ADD);

      doClip(cut);

      if(draw_edges == true){
          glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          glBegin(face_collection.type);

          for (int face_index=0;face_index<face_collection.faces.size();face_index++)
          {
              Face face;
              if(sorting== SORTING_ON)
              {
                  face = face_collection.faces[vp[face_index].second];
              }
              else
              {
                  face = face_collection.faces[face_index];
              }
              float color = face.c;//face_index/(float)face_collection.faces.size() - 0.1;//face.c;//float)// //
              if(face.c < 0.5){
                  color+=0.1;
              }
              else{
                  color-=0.1;
              }
              glColor4f(color, color, color, _alphaNew);
              for(int vertex_index = 0;vertex_index<face.vertices.size();vertex_index++)
              {
                  glVertex3f( face.vertices[vertex_index].x(), face.vertices[vertex_index].y(), face.vertices[vertex_index].z());
                  if(face.vertices[vertex_index].x()>max_value)
                  {
                      max_value = face.vertices[vertex_index].x();
                  }
              }
          }
          glEnd();
      }

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glBegin(face_collection.type);

      float cR = 0;
      float cG = 0;
      float cB = 0;
      for (int face_index=0;face_index<face_collection.faces.size();face_index++)
      {
          Face face;
          if(sorting== SORTING_ON)
          {
              face = face_collection.faces[vp[face_index].second];
          }
          else
          {
              face = face_collection.faces[face_index];
          }

          cR = face.c_R;
          cG = face.c_G;
          cB = face.c_B;
          if(face.c == face_collection.colors[volume_selected])
          {
              cR = (float)colorR/255;
              cG = (float)colorG/255;
              cB = (float)colorB/255;
          }
          glColor4f(cR, cG, cB, _alphaNew);
          for(int vertex_index = 0;vertex_index<face.vertices.size();vertex_index++)
          {
              glVertex3f( face.vertices[vertex_index].x(), face.vertices[vertex_index].y(), face.vertices[vertex_index].z());
              if(face.vertices[vertex_index].x()>max_value)
              {
                  max_value = face.vertices[vertex_index].x();
              }
          }
      }
      glEnd();
      glDisable(GL_BLEND);

  }
}


QVector3D GLWidget::object2view(Face face, GLfloat *model){

    QVector4D center, view_vec;
    QVector3D view_coords;

    center.setX((face.vertices[0].x() + face.vertices[2].x())/2.0);
    center.setY((face.vertices[0].y() + face.vertices[2].y())/2.0);
    center.setZ((face.vertices[0].z() + face.vertices[2].z())/2.0);
    center.setW(1.0);

    view_vec.setX(center.x()*model[0] + center.y()*model[4] + center.z()*model[8] + center.w()*model[12]);
    view_vec.setY(center.x()*model[1] + center.y()*model[5] + center.z()*model[9] + center.w()*model[13]);
    view_vec.setZ(center.x()*model[2] + center.y()*model[6] + center.z()*model[10] + center.w()*model[14]);
    view_vec.setW(center.x()*model[3] + center.y()*model[7] + center.z()*model[11] + center.w()*model[15]);

    view_coords.setX(view_vec.x()/view_vec.w());
    view_coords.setY(view_vec.y()/view_vec.w());
    view_coords.setZ(view_vec.z()/view_vec.w());

    return view_coords;

}

void GLWidget::drawEdges(bool draw){
       draw_edges = draw;
}

void GLWidget::getCutIndex(int index){
       cut = index;
}

void GLWidget::doClip(int index){

    // clipping planes
    GLdouble eqn1[4] = { 1.0, 0.0, 0.0, 0.0};
    GLdouble eqn2[4] = { 0.0, 1.0, 0.0, 0.0 };
    GLdouble eqn3[4] = { 0.0, 0.0, 1.0, 0.0 };
    GLdouble eqn4[4] = { -1.0, 0.0, 0.0, 0.0};
    GLdouble eqn5[4] = { 0.0, -1.0, 0.0, 0.0 };
    GLdouble eqn6[4] = { 0.0, 0.0, -1.0, 0.0 };

    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE2);
    glDisable(GL_CLIP_PLANE3);
    glDisable(GL_CLIP_PLANE4);
    glDisable(GL_CLIP_PLANE5);

    if(index == X_CUT){
            glClipPlane( GL_CLIP_PLANE0, eqn1 );
            glEnable(GL_CLIP_PLANE0);
    }
    else if(index == Y_CUT){
        glClipPlane( GL_CLIP_PLANE1, eqn2 );
        glEnable(GL_CLIP_PLANE1);
    }
    else if(index == Z_CUT){
        glClipPlane( GL_CLIP_PLANE2, eqn3 );
        glEnable(GL_CLIP_PLANE2);
    }
    else if(index == NEG_X_CUT){
        glClipPlane( GL_CLIP_PLANE3, eqn4);
        glEnable(GL_CLIP_PLANE3);
    }
    else if(index == NEG_Y_CUT){
        glClipPlane( GL_CLIP_PLANE4, eqn5);
        glEnable(GL_CLIP_PLANE4);
    }
    else if(index == NEG_Z_CUT){
        glClipPlane( GL_CLIP_PLANE5, eqn6);
        glEnable(GL_CLIP_PLANE5);
    }

}

void GLWidget::getAlpha(int alpha){
    _alphaNew = 1 - ((float)alpha/100.0);
    paintGL();
}

void GLWidget::getFrameBuffer(QString file)
{
    QImage image = grabFramebuffer();
    image.save(file);
}

void GLWidget::get_sorting_index(int index)
{
    sorting = index;
}

void GLWidget::select_volume(int index)
{
    volume_selected = index;
}

void GLWidget::update_volume_color(int R, int G, int B)
{
    colorR = R;
    colorG = G;
    colorB = B;
}

void GLWidget::save_color_volume(void)
{
    for (int face_index=0;face_index<face_collection.faces.size();face_index++)
    {
        if(face_collection.faces[face_index].c == face_collection.colors[volume_selected])
        {
            face_collection.faces[face_index].c_R = (float)colorR/255;
            face_collection.faces[face_index].c_G = (float)colorG/255;
            face_collection.faces[face_index].c_B = (float)colorB/255;
        }
    }
}

void GLWidget::reset_colors(void)
{
    for (int face_index=0;face_index<face_collection.faces.size();face_index++)
    {
            face_collection.faces[face_index].c_R = face_collection.faces[face_index].c;
            face_collection.faces[face_index].c_G = face_collection.faces[face_index].c;
            face_collection.faces[face_index].c_B = face_collection.faces[face_index].c;
    }
}

std::vector<float> GLWidget::get_color_vector(void)
{
    return face_collection.colors;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  // TODO:
  // - Capture mouse motions
  // - If left click is pressed: rotate
  // - If right click is pressed: translate
    //get mouse position
    QPoint displace(0,0);
    QPoint mouse_pos = event->pos();
    /*Code to check in what direction is the button preesed*/
    if( event->buttons() == Qt::RightButton ||  event->buttons() == Qt::LeftButton)
    {
        if((mouse_pos.x()-old_point_t.x()) > 0)
        {

            displace.setX(1);
        }
        if((mouse_pos.x()-old_point_t.x()) < 0)
        {

            displace.setX(-1);
        }

        if((mouse_pos.y()-old_point_t.y()) > 0)
        {
            displace.setY(-1);
        }
        if((mouse_pos.y()-old_point_t.y()) < 0)
        {
            displace.setY(1);
        }
    }
     /***************************************************/

    /* Left button = rotation*/
    if( event->buttons() == Qt::LeftButton)
    {
        rotation.rx()=-displace.x();
        rotation.ry()=displace.y();
        rotation_angle = speed_factor*2;
    }
    /* Right button = Translation*/
    if( event->buttons() == Qt::RightButton)
    {
        translation.rx()= (pow(speed_factor,1.5)*0.02*displace.x());
        translation.ry()= (pow(speed_factor,1.5)*0.02*displace.y());
    }
    /*Update points*/
    old_point_t.setX(mouse_pos.x());
    old_point_t.setY(mouse_pos.y());

    QWidget::update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta();

    if (numDegrees.y() < 0)  zoomScale = (-1);
    if (numDegrees.y() > 0)  zoomScale = 1;
    zoomScale = pow((1.1*speed_factor),zoomScale);
    QWidget::update();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() ==  Qt::Key::Key_Shift)
    {
        speed_factor = 2;
    }
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() ==  Qt::Key::Key_Shift)
    {
        speed_factor = 1;
    }

    if(event->key() == Qt::Key::Key_R)
    {
        auto_rotation = !auto_rotation;
    }
    QWidget::update();
}
