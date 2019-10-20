#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QVector3D>
#include "GL/gl.h"

QJsonArray vectorToJson(const QVector3D &vector);
QVector3D vectorFromJson(const QJsonArray &array);

class Face {
public:
  /* Coordinates of Vertices */
  std::vector<QVector3D> vertices;
  /*Normal vector of the face*/
  QVector3D normal;
  /*Grayscale color - value value between 0-1*/
  float c;
  /*RGB colors for the colorizaiton - values value between 0-1*/
  float c_R;
  float c_G;
  float c_B;

  /*Method to export the face to Json format*/
  QJsonObject toJson() const;
  /*Method to get the face from a Json format*/
  void fromJson(const QJsonObject &json);
};

class FaceCollection {
public:
    /*Class constructor*/
    FaceCollection();
    /*Initial scale*/
    float init_scale = 1;
    /*Vector containing the faces of the object*/
    std::vector<Face> faces;
    /*Vector containing the colors of each of the faces*/
    std::vector<float> colors;
    /*Shape of the face - default value is TRIANGLES*/
    unsigned int type = GL_TRIANGLES;
    /*Defined if the Face colection has been initialized*/
    bool init;

    /*Method to get the Face collection from a Json format*/
    void fromJson(const QJsonArray &json);
    /*Method to get the Face collection from a Stl format*/
    void fromStl(const QString &path);
    /*Method to get the Face collection from a PGM3D format*/
    void frompgm3D(const QString &path);
    /*Method to get the Face collection from a OBJ format*/
    void fromObj(const QString &path);
    /*Method to analyzed the object loaded for first visualization*/
    void analyze_loaded_object(void);
};
