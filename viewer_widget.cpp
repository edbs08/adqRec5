#include "viewer_widget.h"
#include <QResizeEvent>
#include <QFileDialog>
#include <iostream>

using namespace std;
ViewerWidget::ViewerWidget() {
  layout = new QGridLayout(this);
  load_file_button = new QPushButton("Load file");
  save_file_button = new QPushButton("Save Image");
  save_color = new QPushButton("Save Color for Volume");
  gl_widget = new GLWidget(this);

  /*Load file*/
  layout->addWidget(load_file_button, 0, 0);
  connect(load_file_button, SIGNAL(released()), this, SLOT(loadFile()));

  /*Save image*/
  layout->addWidget(save_file_button, 1, 0);
  connect(save_file_button, SIGNAL(released()), this, SLOT(saveImage()));

  int widget_size = 15;
  /*Widget*/
  layout->addWidget(gl_widget,2,0,widget_size,1);

  /*Alpha Slider*/
  QLabel* minimumLabel = new QLabel(tr("Transparency"));
  layout->addWidget(minimumLabel);
  layout->addWidget(slider,widget_size+3,0);
  slider-> setRange(0,100);
  slider-> setTickInterval(1);
  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(alphaSlide(int)));

  /*Sorting option*/
  layout->addWidget(SortingOption,widget_size+4,0);
  SortingOption->addItem("Sorting ON");
  SortingOption->addItem("Sorting OFF");
  connect(SortingOption, SIGNAL(currentIndexChanged(int)), this, SLOT(SortingChanged(int)));

  /*Volume Color option*/
  layout->addWidget(ColorChange, 2,1);
  connect(ColorChange, SIGNAL(currentIndexChanged(int)), this, SLOT(ColorChanged(int)));

  QLabel* Red = new QLabel(tr("R"));
  layout->addWidget(Red,3,1);
  layout->addWidget(slider_R,4,1);
  slider-> setRange(0,255);
  slider-> setTickInterval(1);
  connect(slider_R, SIGNAL(valueChanged(int)), this, SLOT(update_slider_R(int)));

  QLabel* Green = new QLabel(tr("G"));
  layout->addWidget(Green,5,1);
  layout->addWidget(slider_G,6,1);
  slider-> setRange(0,255);
  slider-> setTickInterval(1);
  connect(slider_G, SIGNAL(valueChanged(int)), this, SLOT(update_slider_G(int)));

  QLabel* Blue = new QLabel(tr("B"));
  layout->addWidget(Blue,7,1);
  layout->addWidget(slider_B,8,1);
  slider-> setRange(0,255);
  slider-> setTickInterval(1);
  connect(slider_B, SIGNAL(valueChanged(int)), this, SLOT(update_slider_B(int)));

  layout->addWidget(save_color,9,1);
  connect(save_color, SIGNAL(released()), this, SLOT(saveColor()));


}

void ViewerWidget::reload_buttons(void)
{
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

void ViewerWidget::saveColor(void)
{
    cout<<"save color"<<endl;
    gl_widget ->save_color_volume();
    gl_widget-> update();
}
