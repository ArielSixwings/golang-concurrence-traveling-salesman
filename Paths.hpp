#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <vector>
#include <string>

#define MarsRows 840    //y
#define MarsCols 1035   //x

#define Black 0
#define White 255

//#define Red 10
#define LightRed 15

#define Gold 20
#define LightGold 25

//#define Green 30
#define LightGreen 35

//#define Blue 40
#define LightBlue 45

#define Orchid 50
#define LightOrchid 55

typedef struct
{
    int Row;
    int Col;
}Point;

//A struct that helps me in "move" the point

typedef struct
{
    Point Current;
    Point* Neighbors;
}WalkingPoint;

typedef struct
{
    double Distance;
    long int Key;
}Candidate;

typedef struct
{
    int Blue;
    int Green;
    int Red;
}colortype;

/**
 * @brief      { PaintPixel }
 *
 * @param      Image  The image
 * @param[in]  Row    The row
 * @param[in]  Col    The col
 * @param[in]  color  The color
 */
void PaintPIxel(cv::Mat& Image, int Row,int Col, colortype color);

/**
 * @brief      { function_description }
 *
 * @param      Image  The image
 * @param[in]  Row    The row
 * @param[in]  Col    The col
 * @param[in]  Color  The color
 */
void PaintSquare(cv::Mat& Image, int Row, int Col,colortype color);

/**
 * @brief      { initialize it }
 *
 * @param      NewWalkingPoint  The new walking point
 * @param[in]  Origin           The origin
 */
void InitializeWalkingPoint(WalkingPoint& NewWalkingPoint, Point Origin);

/**
 * @brief      { find the neighbors }
 *
 * @param      CurrentWalkingPoint  The current walking point
 */
void FindNeighBors(WalkingPoint& CurrentWalkingPoint);

/**
 * @brief      { ahmmmm, calculate the euclidian distance }
 *
 * @param[in]  CurrentPoint  The current point
 * @param[in]  Destination   The destination
 *
 * @return     { description_of_the_return_value }
 */
double EuclidianDistances(Point CurrentPoint, Point Destination);

/**
 * @brief      { ahmmmm, sort? }
 *
 * @param      Vector  The vector
 * @param[in]  size    The size
 */
void SelectionSort(Candidate *Vector, uint16_t size);

/**
 * @brief      { calculate and paint best path }
 *
 * @param      ColoredImage  The colored image
 * @param      WorkImage     The work image
 */
long int FindPath(int** Paintmatrix, int** Workmatrix,Point Base, Point destiny,bool red);

/**
 * @brief      { function_description }
 *
 * @param      Image      The image
 * @param      region     The region
 * @param[in]  rowlayers  The rowlayers
 * @param[in]  collayers  The collayers
 * @param[in]  index      The index
 * @param[in]  names  { parameter_description }
 */
void CopyRegion(cv::Mat& Image,cv::Mat& region, int rowlayers, int collayers,int index,char* names);

/**
 * @brief      { Divide the image in rowlayers * collayers images }
 *
 * @param      Image      The image
 * @param[in]  rowlayers  The rowlayers
 * @param[in]  collayers  The collayers
 *
 */
void DivideConquer(cv::Mat& Image,int rowlayers, int collayers);
