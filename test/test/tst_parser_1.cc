
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../viewer/affine.h"
#include "../../viewer/parser.h"


using namespace testing;
using namespace msp;

TEST(parser, parser_1)
{
    msp::Parser parser;
     QString path = "../fortests.txt";

     int answer_v_count = 5;
     int answer_real_e_count = 8;
     int answer_e_array_size = 32;
     double x_min = 0.0, x_max = 1.0, y_min = 0.0, y_max = 1.0;

     parser.GetVertexesCount(path);
     ASSERT_TRUE(msp::DataClass::getDataClass()->getVertex_count() ==
                 answer_v_count);
     parser.GetVertexesAndFacetsCount(path);
     ASSERT_TRUE(msp::DataClass::getDataClass()->getVertex_count() ==
                 answer_v_count);
     parser.GetVertexesArray(path);
     parser.GetEdgeArray(path);
     parser.GetRealEdgeCount();

     ASSERT_TRUE(msp::DataClass::getDataClass()->getVertex_count() ==
                 answer_v_count);
     ASSERT_TRUE(fabs(msp::DataClass::getDataClass()->getSizes().x_min - x_min) < 1e-6);
     ASSERT_TRUE(fabs(msp::DataClass::getDataClass()->getSizes().y_min - y_min) < 1e-6);
     ASSERT_TRUE(fabs(msp::DataClass::getDataClass()->getSizes().x_max - x_max) < 1e-6);
     ASSERT_TRUE(fabs(msp::DataClass::getDataClass()->getSizes().y_max - y_max) < 1e-6);
     ASSERT_TRUE(msp::DataClass::getDataClass()->getEdges_array_count() ==
                 answer_e_array_size);
     ASSERT_TRUE(msp::DataClass::getDataClass()->getEdges_count() ==
                 answer_real_e_count);

}

TEST(affine, affine_move_all) {
  QString path =  "../fortests.txt";
  msp::Parser parser;
  msp::Affine affine;
  QVector3D move_vector = {1.5, 0.3, -1};
  DataClass::getDataClass()->setOffsets(move_vector);
  parser.GetVertexesCount(path);
  parser.GetVertexesArray(path);
  affine.AffineMoveAll();
  ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[0], 1.5, 1e-6);
  ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[1], 0.3, 1e-6);
  ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[2], -1, 1e-6);
}

TEST(affine, affine_move_ox) {
    Affine affine;
    QVector<double> vertexes(15);
     for (std::size_t i = 0; i < 15; ++i) {
       vertexes[i] = i + 3;
     }
     DataClass::getDataClass()->setVertex_data(vertexes);
     DataClass::getDataClass()->setVertex_count(5);
     QVector3D angles = {1, 0, 0};
     DataClass::getDataClass()->setAngles(angles);

     affine.AffineRotateOX();
     double result[15] = {
         3.000000,  -2.046146, 6.067395,  6.000000,  -2.949652,
         10.212715, 9.000000,  -3.853158, 14.358035, 12.000000,
         -4.756664, 18.503355, 15.000000, -5.660170, 22.648675,
     };
     for (std::size_t i = 0; i < 15; i++) {
       ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[i], result[i], 1e-6);
     }
}

TEST(affine, affine_move_oy) {
  Affine affine;
  QVector<double> vertexes(15);
  for (std::size_t i = 0; i < 15; ++i) {
    vertexes[i] = i + 3;
  }
  DataClass::getDataClass()->setVertex_data(vertexes);
  DataClass::getDataClass()->setVertex_count(5);
  QVector3D angles = {0, 1, 0};
  DataClass::getDataClass()->setAngles(angles);
  affine.AffineRotateOY();
  double result[15] = {5.828262,  4.000000,  0.177099,  9.973582,  7.000000,
                       -0.726407, 14.118902, 10.000000, -1.629913, 18.264221,
                       13.000000, -2.533420, 22.409541, 16.000000, -3.436926};
  for (int i = 0; i < 15; i++) {
    ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[i], result[i], 1e-6);
  }
}

TEST(affine, affine_move_oz) {
  Affine affine;
  QVector<double> vertexes(15);
  for (std::size_t i = 0; i < 15; i++) {
    vertexes[i] = i + 3;
  }
  DataClass::getDataClass()->setVertex_data(vertexes);
  DataClass::getDataClass()->setVertex_count(5);
  QVector3D angles = {0, 0, 1};
  DataClass::getDataClass()->setAngles(angles);
  affine.AffineRotateOZ();
  double result[15] = {-1.744977, 4.685622,  5.000000,  -2.648483, 8.830942,
                       8.000000,  -3.551989, 12.976262, 11.000000, -4.455495,
                       17.121582, 14.000000, -5.359001, 21.266902, 17.000000};
  for (int i = 0; i < 15; ++i) {
    ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[i], result[i], 1e-5);
  }
}

TEST(affine, scale) {
  QString path =  "../fortests.txt";
  DataClass::getDataClass()->setScale(15.5);
  Parser parser;
  Affine affine;
  QVector3D move_vector = {1.5, 0.3, -1};
  DataClass::getDataClass()->setOffsets(move_vector);
  parser.GetVertexesCount(path);
  parser.GetVertexesArray(path);
  affine.AffineScale();
  ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[12], 7.75, 1e-6);
  ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[13], 7.75, 1e-6);
  ASSERT_NEAR(DataClass::getDataClass()->getVertex_data()[14], 15.5, 1e-6);
}
