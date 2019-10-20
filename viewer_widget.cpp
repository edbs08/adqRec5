#include "viewer_widget.h"
#include <QResizeEvent>
#include <QFileDialog>
#include <iostream>

/*
 * Constant vales
 */
static const int WINDOW_SIZE = 15;
static const int MAX_SLIDER_VALUE = 255;

/*
 * namespaces
 */
using namespace std;

/*
 * Function and method definitions
 */
ViewerWidget::ViewerWidget() {
  layout = new QGridLayout(this);
  load_file_button = new QPushButton("Load file");
  save_file_button = new QPushButton("Save Image");
  save_color = new QPushButton("Save Color for Volume");
  reset_colors = new QPushButton("Reset Colors");
  gl_widget = new GLWidget(this);
  checkbox = new QCheckBox("Draw Edges", this);

  int col_counter = 0;
  int col_counter2 = 2;

  /*Load file*/
  layout->addWidget(load_file_button, col_counter, 0);
  col_counter++;
  connect(load_file_button, SIGNAL(released()), this, SLOT(loadFile()));


  /*Save image*/
  layout->addWidget(save_file_button, col_counter, 0);
  col_counter++;
  connect(save_file_button, SIGNAL(released()), this, SLOT(saveImage()));

  /*Widget*/
  layout->addWidget(gl_widget,col_counter,0,WINDOW_SIZE,1);
  col_counter+=WINDOW_SIZE;
  col_counter++;

  /*Alpha Slider*/
  QLabel* minimumLabel = new QLabel(tr("Transparency"));
  layout->addWidget(minimumLabel);
  layout->addWidget(slider,col_counter,0);
  col_counter++;
  slider-> setRange(0,100);
  slider-> setTickInterval(1);
  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(alphaSlide(int)));

  /*Sorting option*/
  layout->addWidget(SortingOption,col_counter,0);
  col_counter++;
  SortingOption->addItem("Sorting ON");
  SortingOption->addItem("Sorting OFF");
  connect(SortingOption, SIGNAL(currentIndexChanged(int)), this, SLOT(SortingChanged(int)));

  /*Volume Color option*/
  layout->addWidget(ColorChange, col_counter2,1);
  col_counter2++;
  connect(ColorChange, SIGNAL(currentIndexChanged(int)), this, SLOT(ColorChanged(int)));

  QLabel* Red = new QLabel(tr("R"));
  layout->addWidget(Red,col_counter2,1);
  col_counter2++;
  layout->addWidget(slider_R,col_counter2,1);
  col_counter2++;
  slider-> setRange(0,MAX_SLIDER_VALUE);
  slider-> setTickInterval(1);
  connect(slider_R, SIGNAL(valueChanged(int)), this, SLOT(update_slider_R(int)));

  QLabel* Green = new QLabel(tr("G"));
  layout->addWidget(Green,col_counter2,1);
  col_counter2++;
  layout->addWidget(slider_G,col_counter2,1);
  col_counter2++;
  slider-> setRange(0,MAX_SLIDER_VALUE);
  slider-> setTickInterval(1);
  connect(slider_G, SIGNAL(valueChanged(int)), this, SLOT(update_slider_G(int)));

  QLabel* Blue = new QLabel(tr("B"));
  layout->addWidget(Blue,col_counter2,1);
  col_counter2++;
  layout->addWidget(slider_B,col_counter2,1);
  col_counter2++;
  slider-> setRange(0,MAX_SLIDER_VALUE);
  slider-> setTickInterval(1);
  connect(slider_B, SIGNAL(valueChanged(int)), this, SLOT(update_slider_B(int)));

  layout->addWidget(save_color,col_counter2,1);
  col_counter2++;
  connect(save_color, SIGNAL(released()), this, SLOT(saveColor()));

  layout->addWidget(reset_colors,col_counter2,1);
  col_counter2++;
  connect(reset_colors, SIGNAL(released()), this, SLOT(resetColors()));

  /*Draw Edges option*/
  layout->addWidget(checkbox, col_counter, 0);
  col_counter++;
  connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(getEdgeBool(bool)));

  /*Cutting View Option*/
  layout->addWidget(cutBox,col_counter,0);
  col_counter++;
  cutBox->addItem("No Cut");
  cutBox->addItem("X_Cut");
  cutBox->addItem("NEG_X_Cut");
  cutBox->addItem("Y_Cut");
  cutBox->addItem("NEG_Y_Cut");
  cutBox->addItem("Z_Cut");
  cutBox->addItem("NEG_Z_Cut");
  connect(cutBox, SIGNAL(currentIndexChanged(int)), this, SLOT(cutBoxIndex(int)));
}

void ViewerWidget::reload_buttons(void)
{
    ColorChange->clear();
    std::vector<float> colors = gl_widget->get_color_vector();
    for(uint8_t index = 0;index<colors.size();index++)
    {
        QString name;
        if(index == 0)
        {
            name = "No volume selected";
        }
        else
        {
            name = "Volume " + QString::number(index);
        }

        ColorChange->addItem(name);
    }
}

void ViewerWidget::loadFile() {  
  QString file_name= QFileDialog::getOpenFileName(this, ("Open File"),QDir::currentPath(), ("Document files (*.json *.stl *.obj *.pgm3d)"));
  gl_widget->loadFaces(file_name);
  reload_buttons();
  gl_widget-> update();
}

void ViewerWidget::saveImage() {
  QString file_name= QFileDialog::getSaveFileName(this, tr("Save File"),"untitled.png",tr("Images (*.png *.xpm *.jpg)"));
  gl_widget-> getFrameBuffer(file_name);
  gl_widget-> update();
}

void ViewerWidget::alphaSlide(int alpha){
    gl_widget-> getAlpha(alpha);
    gl_widget-> update();
}

void ViewerWidget::SortingChanged(int index){
    gl_widget-> get_sorting_index(index);
    gl_widget-> update();
}

void ViewerWidget::ColorChanged(int index)
{
    gl_widget->select_volume(index);
    gl_widget-> update();
}

void ViewerWidget::update_slider_R(int R)
{
    sliderR = R;
    gl_widget ->update_volume_color(sliderR,sliderG,sliderB);
    gl_widget-> update();

}
void ViewerWidget::update_slider_G(int G)
{
    sliderG = G;
    gl_widget ->update_volume_color(sliderR,sliderG,sliderB);
    gl_widget-> update();

}
void ViewerWidget::update_slider_B(int B)
{
    sliderB = B;
    gl_widget ->update_volume_color(sliderR,sliderG,sliderB);
    gl_widget-> update();
}

void ViewerWidget::saveColor(void)
{
    gl_widget ->save_color_volume();
    gl_widget-> update();
}

void ViewerWidget::resetColors(void)
{
    gl_widget->reset_colors();
    ColorChange->setCurrentIndex(0);
    gl_widget-> update();
}

void ViewerWidget::cutBoxIndex(int index){
    gl_widget-> getCutIndex(index);
    gl_widget-> update();
}

void ViewerWidget::getEdgeBool(bool draw){
    gl_widget -> drawEdges(draw);
    gl_widget -> update();
}
