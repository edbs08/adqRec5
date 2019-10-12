#pragma once

#include <QGridLayout>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>

#include "glwidget.h"

class ViewerWidget : public QWidget {
public:
  Q_OBJECT
public:
  ViewerWidget();

  QGridLayout *layout;
  QPushButton *load_file_button;
  QPushButton *save_file_button;
  GLWidget *gl_widget;

  QSlider *slider = new QSlider(Qt::Horizontal);
  QComboBox * SortingOption = new QComboBox();
  QComboBox * ColorChange = new QComboBox();
  QSlider *slider_R = new QSlider(Qt::Horizontal);
  QSlider *slider_G = new QSlider(Qt::Horizontal);
  QSlider *slider_B = new QSlider(Qt::Horizontal);
  int sliderR = 0;
  int sliderG = 0;
  int sliderB = 0;
  QPushButton *save_color;

  void reload_buttons(void);

public slots:
  void alphaSlide(int);
  void loadFile();
  void saveImage();
  void SortingChanged(int);
  void ColorChanged(int index);
  void update_slider_R(int R);
  void update_slider_G(int G);
  void update_slider_B(int B);
  void saveColor(void);
};
