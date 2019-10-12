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

  void reload_buttons(void);

public slots:
  void alphaSlide(int);
  void loadFile();
  void saveImage();
  void SortingChanged(int);
};
