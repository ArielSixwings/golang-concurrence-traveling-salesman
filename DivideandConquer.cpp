#include "Paths.hpp"
#include <opencv2/highgui.hpp>


void CopyRegion(cv::Mat& Image,cv::Mat& region, int rowlayers, int collayers,int index){
    char names[rowlayers*collayers][30] = {"./regions/region00.jpg",
                                         "./regions/region01.jpg",
                                         "./regions/region02.jpg",
                                         "./regions/region03.jpg",
                                         "./regions/region04.jpg",
                                         "./regions/region05.jpg",
                                         "./regions/region06.jpg",
                                         "./regions/region07.jpg",
                                         "./regions/region08.jpg",
                                         "./regions/region09.jpg",
                                         "./regions/region10.jpg",
                                         "./regions/region11.jpg",
                                         "./regions/region12.jpg",
                                         "./regions/region13.jpg",
                                         "./regions/region14.jpg",
                                         "./regions/region15.jpg",
                                         "./regions/region16.jpg",
                                         "./regions/region17.jpg",
                                         "./regions/region18.jpg",
                                         "./regions/region19.jpg",
                                         "./regions/region20.jpg",
                                         "./regions/region21.jpg",
                                         "./regions/region22.jpg",
                                         "./regions/region23.jpg"};

    int originrow;
    int origincol;
    std::cin>>origincol>>originrow;
    for (int i = 0; i < (Image.rows/rowlayers); ++i){
        for (int j = 0; j < (Image.cols/collayers); ++j){
            region.at<cv::Vec3b>(i,j)[2] =  Image.at<cv::Vec3b>(i+originrow,j+origincol)[2];
            region.at<cv::Vec3b>(i,j)[1] =  Image.at<cv::Vec3b>(i+originrow,j+origincol)[1];
            region.at<cv::Vec3b>(i,j)[0] =  Image.at<cv::Vec3b>(i+originrow,j+origincol)[0];
        }
    }
    int spotrow;
    int spotcol;
    for (int i = 0; i < 8; ++i){
        std::cin>>spotcol>>spotrow;
        std::cout<<(spotcol+origincol)<<" "<<(spotrow+originrow)<<std::endl;
    }
    cv::imshow( "region", region );
    cv::imwrite(names[index],region);
    cv::waitKey(500);
}
/**
 * @brief      { Divide the image in rowlayers * collayers images }
 *
 * @param      Image      The image
 * @param[in]  rowlayers  The rowlayers
 * @param[in]  collayers  The collayers
 *
 */
void DivideConquer(cv::Mat& Image,int rowlayers, int collayers){
    cv::Mat auxr;
    auxr = cv::imread("aux.jpg", CV_LOAD_IMAGE_COLOR);
    int index = 0;
    for (int i = 0; i < rowlayers; ++i){
        for (int j = 0; j < collayers; ++j){
            //std::cout<<"building region"<<index<<std::endl;
            CopyRegion(Image,auxr,rowlayers,collayers,index);
            index++;
        }
    }
}
int main(int argc, char const *argv[]){
    cv::Mat midgar;
    midgar = cv::imread("./imageprocessing/Images/midgard.jpg", CV_LOAD_IMAGE_COLOR);
    DivideConquer(midgar,4,6);
}
