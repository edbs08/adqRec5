#include "viewer_widget.h"
#include <QResizeEvent>
#include <QFileDialog>
#include <iostream>

ViewerWidget::ViewerWidget() {
  layout = new QGridLayout(this);
  load_file_button = new QPushButton("Load file");
  save_file_button = new QPushButton("Save Image");

  gl_widget = new GLWidget(this);

  layout->addWidget(load_file_button, 0, 0);
  connect(load_file_button, SIGNAL(released()), this, SLOT(loadFile()));

  layout->addWidget(save_file_button, 1, 0);
  connect(save_file_button, SIGNAL(released()), this, SLOT(saveImage()));

  layout->addWidget(gl_widget, 2, 0);
  /*Alpha Slider*/
  layout->addWidget(slider,3,0);
  slider-> setRange(0,100);
  slider-> setTickInterval(1);
  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(alphaSlide(int)));

  /*Sorting option*/
  layout->addWidget(SortingOption,4,0);
  SortingOption->addItem("Sorting ON");
  SortingOption->addItem("Sorting OFF");
  connect(SortingOption, SIGNAL(currentIndexChanged(int)), this, SLOT(SortingChanged(int)));

  /*Volume Color option*/
  layout->addWidget(gl_widget, 5, 0);
  layout->addWidget(ColorChange);
  connect(ColorChange, SIGNAL(currentIndexChanged(int)), this, SLOT(ColorChanged(int)));

  layout->addWidget(slider_R);
  slider-> setRange(0,255);
  slider-> setTickInterval(1);
  connect(slider_R, SIGNAL(valueChanged(int)), this, SLOT(update_slider_R(int)));

  layout->addWidget(slider_G);
  slider-> setRange(0,255);
  slider-> setTickInterval(1);
  connect(slider_G, SIGNAL(valueChanged(int)), this, SLOT(update_slider_G(int)));

  layout->addWidget(slider_B);
  slider-> setRange(0,255);
  slider-> setTickInterval(1);
  connect(slider_B, SIGNAL(valueChanged(int)), this, SLOT(update_slider_B(int)));
}

void ViewerWidget::reload_buttons(void)
{
    std::vector<float> colors = gl_widget->get_color_vector();
    for(uint8_t index = 0;index<colors.size();index++)
    {
        QString name = "Volume " + QString::number(index);
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
    std::cout<<"test"<<std::endl;
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
