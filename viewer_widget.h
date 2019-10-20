#pragma once

#include <QGridLayout>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>
#include <QLabel>
#include<QCheckBox>
#include "glwidget.h"

class ViewerWidget : public QWidget {
public:
  Q_OBJECT
public:
  /*Class constructor*/
  ViewerWidget();
  /*Grid layout*/
  QGridLayout *layout;
  /*Interface Push buttons*/
  QPushButton *load_file_button;
  QPushButton *save_file_button;
  GLWidget *gl_widget;
  QPushButton *save_color;
  QPushButton *reset_colors;
  /*Interface sliders*/
  QSlider *slider = new QSlider(Qt::Horizontal);
  QSlider *slider_R = new QSlider(Qt::Horizontal);
  QSlider *slider_G = new QSlider(Qt::Horizontal);
  QSlider *slider_B = new QSlider(Qt::Horizontal);
  /*Holds the values of the RGB sliders*/
  int sliderR = 0;
  int sliderG = 0;
  int sliderB = 0;
  /*Interface Combo boxes*/
  QComboBox * SortingOption = new QComboBox();
  QComboBox * ColorChange = new QComboBox();
  QComboBox * cutBox = new QComboBox();
  /*Interface Checkboxes*/
  QCheckBox *checkbox;
  /*Reload the interface buttons based on the object loaded*/
  void reload_buttons(void);

public slots:
  /*Gets the value of the Alpha slider*/
  void alphaSlide(int);
  /*Gets the users input of the load file button*/
  void loadFile();
  /*Gets the users input of the save image button*/
  void saveImage();
  /*Gets the users input of the sorting option*/
  void SortingChanged(int);
  /*Gets the users input of the volume color*/
  void ColorChanged(int index);
  /*Gets the users input for the sliders*/
  void update_slider_R(int R);
  void update_slider_G(int G);
  void update_slider_B(int B);
  /*Gets the users input of the save color button*/
  void saveColor(void);
  /*Gets the users input of the reset colors button*/
  void resetColors(void);
  /*Gets the users input of the edges checkbox*/
  void getEdgeBool(bool draw);
  /*Gets the users input of cut view functionality*/
  void cutBoxIndex(int index);
};
