#include "myopenglwidjet.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent) {
  setGeometry(400, 200, 800, 600);
}

glView::~glView() {}

void glView::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0., 0., -2.);
}

void glView::resizeGL(int w, int h) {}

void glView::changeProjection() {
  if (msp::DataClass::getDataClass()->getIsOrthogonal()) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double max = (msp::DataClass::getDataClass()->getSizes().x_max * 1.5);
    glOrtho(-max, max, -max, max, -99999999999, 99999999999);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double max = (msp::DataClass::getDataClass()->getSizes().x_max * 1.5);
    glOrtho(-max, max, -max, max, -99999999999, 99999999999);
    float fov = 5.0 * M_PI / 180;
    float heapHeight = 580 / (2 * tan(fov / 2));
    float far = 100000;
    glFrustum(-510, 510, -580, 580, heapHeight, far);
  }
}

void glView::paintGL() {
  if (msp::DataClass::getDataClass()->getIsProjection()) changeProjection();
  msp::DataClass::getDataClass()->getBackground_color().getRgbF(
      msp::DataClass::getDataClass()->getBackground_red(),
      msp::DataClass::getDataClass()->getBackgroundGreen(),
      msp::DataClass::getDataClass()->getBackgroundBlue(),
      msp::DataClass::getDataClass()->getBackgroundAlpha());

  glClearColor(*msp::DataClass::getDataClass()->getBackground_red(),
               *msp::DataClass::getDataClass()->getBackgroundGreen(),
               *msp::DataClass::getDataClass()->getBackgroundBlue(),
               *msp::DataClass::getDataClass()->getBackgroundAlpha());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glVertexPointer(3, GL_DOUBLE, 0,
                  msp::DataClass::getDataClass()->getVertex_data().data());
  glEnableClientState(GL_VERTEX_ARRAY);
  if (msp::DataClass::getDataClass()->getVertice_type() != 0) {
    if (msp::DataClass::getDataClass()->getVertice_type() == 1)
      glEnable(GL_POINT_SMOOTH);
    else
      glDisable(GL_POINT_SMOOTH);
    glPointSize(msp::DataClass::getDataClass()->getVertices_size());
    msp::DataClass::getDataClass()->getVertices_color().getRgbF(
        msp::DataClass::getDataClass()->getVertice_red(),
        msp::DataClass::getDataClass()->getVertice_green(),
        msp::DataClass::getDataClass()->getVertice_blue());
    glColor3d(*msp::DataClass::getDataClass()->getVertice_red(),
              *msp::DataClass::getDataClass()->getVertice_green(),
              *msp::DataClass::getDataClass()->getVertice_blue());
    glDrawArrays(GL_POINTS, 0,
                 msp::DataClass::getDataClass()->getVertex_count());
  }
  msp::DataClass::getDataClass()->getEdges_color().getRgbF(
      msp::DataClass::getDataClass()->getEdge_red(),
      msp::DataClass::getDataClass()->getEdge_green(),
      msp::DataClass::getDataClass()->getEdge_blue());
  glColor3d(*msp::DataClass::getDataClass()->getEdge_red(),
            *msp::DataClass::getDataClass()->getEdge_green(),
            *msp::DataClass::getDataClass()->getEdge_blue());
  glLineWidth(msp::DataClass::getDataClass()->getLine_thickness());
  glLineStipple(1, 0x3333);
  if (msp::DataClass::getDataClass()->getLine_type())
    glEnable(GL_LINE_STIPPLE);
  else
    glDisable(GL_LINE_STIPPLE);

  glDrawElements(
      GL_LINES, msp::DataClass::getDataClass()->getEdges_array_count(),
      GL_UNSIGNED_INT, msp::DataClass::getDataClass()->getEdges_data().data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::mousePressEvent(QMouseEvent *apEvent) {
  controller_->MousePressEvent(apEvent);
}

void glView::mouseMoveEvent(QMouseEvent *apEvent) {
  double xMouseRot = (0.001 / M_PI *
                          (apEvent->pos().y() -
                           msp::DataClass::getDataClass()->position().y()) +
                      msp::DataClass::getDataClass()->getAngles().x());
  double yMouseRot = (0.001 / M_PI *
                          (apEvent->pos().x() -
                           msp::DataClass::getDataClass()->position().x()) +
                      msp::DataClass::getDataClass()->getAngles().y());
  controller_->MouseRotation(xMouseRot * 10, yMouseRot * 10);
}

void glView::Update() { update(); }

void glView::SetController(msp::Controller *controller) {
  controller_ = controller;
}
