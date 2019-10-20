#pragma once

#include <QMatrix4x4>
#include <QOpenGLWidget>
#include <QString>
#include <QWidget>
#include <QtGui>
#include <string>

#include "face.h"

class GLWidget : public QOpenGLWidget {
public:
  Q_OBJECT
    /* Constant options for the sorting */
    static const int SORTING_ON = 0;
    static const int SORTING_OFF = 1;
    /* Constant options for the plane cutting */
    static const int NO_CUT = 0;
    static const int X_CUT = 1;
    static const int NEG_X_CUT = 2;
    static const int Y_CUT = 3;
    static const int NEG_Y_CUT = 4;
    static const int Z_CUT = 5;
    static const int NEG_Z_CUT = 6;

    /*Defines the users input of the sorting */
    int sorting = 0;
    /*Defines the users input of the volume coloring */
    int volume_selected = 0;
    /*Defines the users input of the cut plane */
    int cut = 0;
    /*Defines the users input of the alpha transparency */
    float _alphaNew = 1;
    /*Defines the users input of the edges drawing */
    bool draw_edges = false;
    /*Defines the users input for the auto rotation */
    bool auto_rotation = false;

    /*Speed factor of the funcitonalities*/
    float speed_factor = 1;
    /*Rotation angle of the object*/
    float rotation_angle=0;
    /*Rotation vector of the object*/
    QPointF rotation=QPoint(1.0f,0.0f);
    /*Translation vector of the object*/
    QPointF translation=QPoint(0.0f,0.0f);
    /*Zoom scalar for the visualization of the object*/
    float zoomScale=1.0f;
    /*Array to hold the values of the Model View matrix*/
    GLfloat m[16]={};
    /*Holds the value of the last point of the mouse*/
    QPoint old_point_t=QPoint(0.0f,0.0f);

    /*Holds the temporal RGB values of the volumes*/
    int colorR = 0;
    int colorG = 0;
    int colorB = 0;
    /*Defines if is the first time the funciton PaintGL is called*/
    bool first_paint = true;
public:
    /*Class constructor*/
  GLWidget(QWidget *parent = 0);
  /*Class destructor*/
  ~GLWidget();
  /*States the size of the window*/
  QSize sizeHint() const { return QSize(400, 400); }
  /*Get the relative distance to the image plane of the faces*/
  QVector3D object2view(Face face, GLfloat *model);
  /*Load the faces from a file*/
  void loadFaces(const QString &path);
  /*Method to update the alpha value*/
  void getAlpha(int);
  /*Get the frane buffer to save as image*/
  void getFrameBuffer(QString file);
  /*Get the users input fo the face sorting functionality*/
  void get_sorting_index(int index);
  /*Get the users input fo the dawing edges functionality*/
  void drawEdges(bool draw);
  /*Get the users input fo the plane cut functionality*/
  void getCutIndex(int index);
  /*Get the users input fo the volume selection and coloring functionality*/
  void select_volume(int index);
  /*Performs the cutting view of the object*/
  void doClip(int index);
  /*Returns the color vector from the Face collection*/
  std::vector<float> get_color_vector(void);
  /*Update the colors of the volume*/
  void update_volume_color(int R, int G, int B);
  /*Saves the current colors for the selected volume*/
  void save_color_volume(void);
  /*Sets the colors to its original grayscale value*/
  void reset_colors(void);
  /*Check the file extension of the loaded file*/
  std::string getFileExt(const QString& s);
  /*Resets the variables after loding a new files*/
  void clear_variables(void);

protected:
  /*Init GL*/
  void initializeGL() override;
  /*Paint the object*/
  void paintGL() override;
  /*Returs the wheel event of the mouse*/
  void wheelEvent(QWheelEvent *event) override;
  /*Returs the move event of the mouse*/
  void mouseMoveEvent(QMouseEvent *event) override;
  /*Returns the key pressed event*/
  void keyPressEvent(QKeyEvent *event) override;
  /*Returns the key released event*/
  void keyReleaseEvent(QKeyEvent *event) override;

  /*Holds the loaded face collection*/
  FaceCollection face_collection;
};
