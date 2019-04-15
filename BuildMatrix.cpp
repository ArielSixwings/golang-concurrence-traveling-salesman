#include "Paths.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char const *argv[]){
    int index;
    std::cin>>index;

    char jpgnames[25][40] = {
                "./imageprocessing/Images/midgardhist.jpg",
                "./regions/hist/histregion00.jpg",
                "./regions/hist/histregion01.jpg",
                "./regions/hist/histregion02.jpg",
                "./regions/hist/histregion03.jpg",
                "./regions/hist/histregion04.jpg",
                "./regions/hist/histregion05.jpg",
                "./regions/hist/histregion06.jpg",
                "./regions/hist/histregion07.jpg",
                "./regions/hist/histregion08.jpg",
                "./regions/hist/histregion09.jpg",
                "./regions/hist/histregion10.jpg",
                "./regions/hist/histregion11.jpg",
                "./regions/hist/histregion12.jpg",
                "./regions/hist/histregion13.jpg",
                "./regions/hist/histregion14.jpg",
                "./regions/hist/histregion15.jpg",
                "./regions/hist/histregion16.jpg",
                "./regions/hist/histregion17.jpg",
                "./regions/hist/histregion18.jpg",
                "./regions/hist/histregion19.jpg",
                "./regions/hist/histregion20.jpg",
                "./regions/hist/histregion21.jpg",
                "./regions/hist/histregion22.jpg",
                "./regions/hist/histregion23.jpg"};

    work = cv::imread(jpgnames[index], CV_LOAD_IMAGE_UNCHANGED);
    for (int i = 0; i < work.rows(); ++i){
        for (int j = 0; j < count; ++j){
            std::cout<<work.at<uint8_t>(i,j)<<",";
        }
        std::cout<<std::endl;
    }
    return 0;
}
