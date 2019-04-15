#include "Paths.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void PaintPixel(cv::Mat& Image, int Row,int Col, colortype color){
    Image.at<cv::Vec3b>(Row,Col)[2] = color.Red;
    Image.at<cv::Vec3b>(Row,Col)[1] = color.Green;
    Image.at<cv::Vec3b>(Row,Col)[0] = color.Blue;
}

void PaintSquare(cv::Mat& Image, int Row, int Col,colortype color){
    //center
    PaintPixel(Image,Row,Col,color);
    PaintPixel(Image,Row+1,Col,color);
    PaintPixel(Image,Row-1,Col,color);
    PaintPixel(Image,Row,Col+1,color);
    PaintPixel(Image,Row,Col-1,color);
    PaintPixel(Image,Row+1,Col+1,color);
    PaintPixel(Image,Row+1,Col-1,color);
    PaintPixel(Image,Row-1,Col+1,color);
    PaintPixel(Image,Row-1,Col-1,color);

    //vertical
    for (int c = (Col+4); c < (Col+12); ++c){
        for (int r = (Row-10); r < (Row+10); ++r){
            PaintPixel(Image,r,c,color);
        }
    }
    for (int c = (Col-12); c < (Col-4); ++c){
        for (int r = (Row-10); r < (Row+10); ++r){
            PaintPixel(Image,r,c,color);
        }
    }


    //horizontal
    for (int r = (Row+4); r < (Row+12); ++r){
        for (int c = (Col-10); c < (Col+10); ++c){
            PaintPixel(Image,r,c,color);
        }
    }
    for (int r = (Row-12); r < (Row-4); ++r){
        for (int c = (Col-10); c < (Col+10); ++c){
            PaintPixel(Image,r,c,color);
        }
    }
}

void InitializeWalkingPoint(WalkingPoint& NewWalkingPoint, Point Origin){
    NewWalkingPoint.Current.Row = Origin.Row;
    NewWalkingPoint.Current.Col = Origin.Col;
    NewWalkingPoint.Neighbors = (Point*)calloc(8,sizeof(Point));
}

void FindNeighBors(WalkingPoint& CurrentWalkingPoint){
    //N4----------------------------
    CurrentWalkingPoint.Neighbors[1].Row = (CurrentWalkingPoint.Current.Row)+1;
    CurrentWalkingPoint.Neighbors[1].Col = CurrentWalkingPoint.Current.Col;

    CurrentWalkingPoint.Neighbors[3].Row = CurrentWalkingPoint.Current.Row;
    CurrentWalkingPoint.Neighbors[3].Col = (CurrentWalkingPoint.Current.Col)+1;

    CurrentWalkingPoint.Neighbors[5].Row = (CurrentWalkingPoint.Current.Row)-1;
    CurrentWalkingPoint.Neighbors[5].Col =  CurrentWalkingPoint.Current.Col;

    CurrentWalkingPoint.Neighbors[7].Row = CurrentWalkingPoint.Current.Row;
    CurrentWalkingPoint.Neighbors[7].Col = (CurrentWalkingPoint.Current.Col)-1;

    //ND----------------------------------------------------------------------------
    CurrentWalkingPoint.Neighbors[0].Row = (CurrentWalkingPoint.Current.Row)+1;
    CurrentWalkingPoint.Neighbors[0].Col = (CurrentWalkingPoint.Current.Col)-1;

    CurrentWalkingPoint.Neighbors[2].Row = (CurrentWalkingPoint.Current.Row)+1;
    CurrentWalkingPoint.Neighbors[2].Col = (CurrentWalkingPoint.Current.Col)+1;

    CurrentWalkingPoint.Neighbors[4].Row = (CurrentWalkingPoint.Current.Row)-1;
    CurrentWalkingPoint.Neighbors[4].Col = (CurrentWalkingPoint.Current.Col)+1;

    CurrentWalkingPoint.Neighbors[6].Row = (CurrentWalkingPoint.Current.Row)-1;
    CurrentWalkingPoint.Neighbors[6].Col = (CurrentWalkingPoint.Current.Col)-1;
}

double EuclidianDistances(Point CurrentPoint, Point Destination){
    double DeltaRow;
    double DeltaCol;
    double Distance;
    DeltaRow = (double)(Destination.Row - CurrentPoint.Row);
    DeltaCol = (double)(Destination.Col - CurrentPoint.Col);
    Distance = sqrt(pow(DeltaRow,2) + pow(DeltaCol,2));
    return Distance;
}

void SelectionSort(Candidate *Vector, uint16_t size){
    if ((Vector == NULL) || (size < 2))
    {
        return;
    }
    int16_t Smallest, i, j;
    Candidate temp;
    for (i = 0; i < (size-1); ++i)
    {
        Smallest = i;
        for (j = i+1; j < size; ++j)
        {
            if (Vector[Smallest].Distance > Vector[j].Distance)
            {
                Smallest = j;
            }
        }
        temp.Distance = Vector[i].Distance;
        temp.Key = Vector[i].Key;

        Vector[i].Distance = Vector[Smallest].Distance;
        Vector[i].Key = Vector[Smallest].Key;

        Vector[Smallest].Distance = temp.Distance;
        Vector[Smallest].Key = temp.Key;
    }
}

long int FindPath(int** Paintmatrix, int** Workmatrix,Point Base, Point destiny,bool red){
    int AuxRow;
    int AuxCol;
    int AuxGreyLevel;
    Point base;
    Point Destination;
    WalkingPoint WorkPoint;

    base.Row = Base.Row;
    base.Col = Base.Col;

    Destination.Row = destiny.Row;
    Destination.Col = destiny.Col;
    InitializeWalkingPoint(WorkPoint,base);
    long int dist = 0;
    Candidate* Candidates = (Candidate*)calloc(8,sizeof(Candidate));
    for (int i = 0;((WorkPoint.Current.Row != Destination.Row) || (WorkPoint.Current.Col != Destination.Col)); ++i){
        std::cout<<"iteration: "<<i<<std::endl;
        //std::cout<<"iteration  "<<i<<std::endl;
        FindNeighBors(WorkPoint);
        for (int j = 0; j < 8; ++j){
            Candidates[j].Key = j; //with that , i have a nice way to access the neibors in the future
            Candidates[j].Distance = EuclidianDistances(WorkPoint.Neighbors[j],Destination);
        }
        int pato = 1;
        SelectionSort(Candidates,8);
        pato = 2;

        /*AuxRow And AuxCol, in this part, are used to access the gray level
        of the 3 neighbors with the smallests distances to the destination */

        for (int auxindexC = 0; auxindexC < 3; ++auxindexC){
            AuxRow = WorkPoint.Neighbors[Candidates[auxindexC].Key].Row;
            AuxCol = WorkPoint.Neighbors[Candidates[auxindexC].Key].Col;
            Candidates[auxindexC].Distance = (Candidates[auxindexC].Distance * (int)Workmatrix[AuxRow][AuxCol]);
        }

        SelectionSort(Candidates,3);

        AuxRow = WorkPoint.Neighbors[Candidates[0].Key].Row;
        AuxCol = WorkPoint.Neighbors[Candidates[0].Key].Col;
        for (int i = 0; i < 7; ++i){
            if (AuxRow >= 4320){
                std::cout<<"next pixel is invalid"<<std::endl;
                AuxRow = WorkPoint.Neighbors[Candidates[i+1].Key].Row;
                AuxCol = WorkPoint.Neighbors[Candidates[i+1].Key].Col;
            }
        }
        dist = dist + (int)(Workmatrix[AuxRow][AuxCol]);

        if( red ){
            Paintmatrix[AuxRow][AuxCol] = 72;
        }
        else{
            Paintmatrix[AuxRow][AuxCol] = 0;
        }

        WorkPoint.Current.Row = AuxRow;
        WorkPoint.Current.Col = AuxCol;

    }

    if (dist == 0){
        std::cout<<"dist is 0, is it right"<<std::endl;
        std::cout<<Base.Row<<" "<<Base.Col<<"----------------"<<destiny.Row<<" "<<destiny.Col<<std::endl;
    }
    return dist;
}
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
    cv::imshow( "region", region );
    cv::imwrite(names[index],region);
    cv::waitKey(500);
}

void DivideConquer(cv::Mat& Image,int rowlayers, int collayers){
    cv::Mat auxr;
    auxr = cv::imread("aux.jpg", CV_LOAD_IMAGE_COLOR);
    int index = 0;
    for (int i = 0; i < rowlayers; ++i){
        for (int j = 0; j < collayers; ++j){
            std::cout<<"building region"<<index<<std::endl;
            CopyRegion(Image,auxr,rowlayers,collayers,index);
            index++;
        }
    }
}

int main(int argc, char const *argv[]){

    std::cout<<1<<std::endl;

    int indexname;
    int sub;
    int donecall;
    int divide;
    int failpaths = 0;
    int failspots[192][2];

    char names[24][30] = {
        "./regions/region00.jpg",
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

    char worknames[24][40] = {
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

    char savenames[24][30] = {
        "./results/paths/path00.jpg",
        "./results/paths/path01.jpg",
        "./results/paths/path02.jpg",
        "./results/paths/path03.jpg",
        "./results/paths/path04.jpg",
        "./results/paths/path05.jpg",
        "./results/paths/path06.jpg",
        "./results/paths/path07.jpg",
        "./results/paths/path08.jpg",
        "./results/paths/path09.jpg",
        "./results/paths/path10.jpg",
        "./results/paths/path11.jpg",
        "./results/paths/path12.jpg",
        "./results/paths/path13.jpg",
        "./results/paths/path14.jpg",
        "./results/paths/path15.jpg",
        "./results/paths/path16.jpg",
        "./results/paths/path17.jpg",
        "./results/paths/path18.jpg",
        "./results/paths/path19.jpg",
        "./results/paths/path20.jpg",
        "./results/paths/path21.jpg",
        "./results/paths/path22.jpg",
        "./results/paths/path23.jpg"};

    cv::Mat allmidgard;
    cv::Mat allwork;
    cv::Mat midgard;
    cv::Mat work;

    //std::cout<<"provide indexname, divide, sub and donecall "<<std::endl;
    std::cin>>indexname;
    std::cin>>divide;
    std::cin>>sub;
    std::cin>>donecall;
    allmidgard = cv::imread("./imageprocessing/Images/midgard.jpg", CV_LOAD_IMAGE_COLOR);
    allwork = cv::imread("./imageprocessing/Images/midgardhist.jpg", CV_LOAD_IMAGE_COLOR);
    midgard = cv::imread(names[indexname], CV_LOAD_IMAGE_COLOR);
    work = cv::imread(worknames[indexname], CV_LOAD_IMAGE_COLOR);


    if (divide) DivideConquer(midgard,4,6);


    Point base;
    Point spot;
    int* path = new int[193];

    int** s = new int*[192];

    for(int i = 0; i < (192); ++i)
        s[i] = new int[192];

    int** Workregion = new int*[1080+100];
    for(int i = 0; i < (1080+100); ++i)
        Workregion[i] = new int[1280+100];

    int** Paintregion = new int*[1080+100];
    for(int i = 0; i < (1080+100); ++i)
        Paintregion[i] = new int[1280+100];

    for (int i = 0; i < 1080; ++i){
        for (int j = 0; j < 1280; ++j){
            Workregion[i][j] = work.at<uint8_t>(i,j);
            Paintregion[i][j] = -1;
        }
    }


    int** Workmatrix = new int*[4320+100];
    for(int i = 0; i < (4320+100); ++i)
        Workmatrix[i] = new int[7680+100];


    int** Paintmatrix = new int*[4320+100];
    for(int i = 0; i < (4320+100); ++i)
        Paintmatrix[i] = new int[7680+100];
    for (int i = 0; i < 4320; ++i){
        for (int j = 0; j < 7680; ++j){
            Workmatrix[i][j] = allwork.at<uint8_t>(i,j);
            Paintmatrix[i][j] = -1;
        }
    }

    int bases[192][2];
    int destinys[192][2];
    int spots[192][2];

    colortype red{0,0,102};
    colortype blue{76,9,0};

    if (sub){
        for (int i = 0; i < 8; ++i){
            std::cin>>spots[i][0];
            std::cin>>spots[i][1];
        }
    }
    else{
        if (donecall){
            for (int i = 0; i < 193; ++i){//read the path
                std::cin>>path[i];
            }
        }
        for (int i = 0; i < 192; ++i){
            std::cin>>spots[i][1]>>spots[i][0];
            bases[i][1] = spots[i][1];
            bases[i][0] = spots[i][0];
        }
        for (int i = 0; i < 192; ++i){
            bases[i][0] = spots[path[i]][0];
            bases[i][1] = spots[path[i]][0];
            destinys[i][0] = spots[path[i+1]][0];
            destinys[i][1] =  spots[path[i+1]][0];
        }

    }
    bool doit[8*8];
    for (int i = 0; i < 64; ++i){
        doit[i] = true;
    }
    for (int i = 0; i < 8; ++i){
        doit[i*8+i] = false;
    }
    if (sub){
        for (int i = 0; i < 8; ++i){
            PaintSquare(midgard,spots[i][1],spots[i][0],red);
            base.Col = spots[i][0];
            base.Row = spots[i][1];
            for (int j = 0; j < 8; ++j){
                if (doit[(i*8)+j]){
                    std::cin>>spot.Col>>spot.Row;

                    long int dist;

                    dist = FindPath(Paintregion,Workregion,base,spot,false);
                    std::cout<<(i+1)<<" "<<(j+1)<<" "<<dist<<std::endl;
                    dist = FindPath(Paintregion,Workregion,spot,base,false);
                    std::cout<<(j+1)<<" "<<(i+1)<<" "<<dist<<std::endl;

                    doit[(i*8)+j] = false;
                }
                else{
                    continue;
                }
            }
        }
    }
    else{
        bool doit[192*192];
        for (int i = 0; i < 36864; ++i){
            doit[i] = true;
        }
        for (int i = 0; i < 192; ++i){
            doit[i*192+i] = false;
        }
        if (donecall){
            for (int i = 0; i < 192; ++i){
                PaintSquare(allmidgard,spots[path[i]][1],spots[path[i]][0],red);

                base.Col = bases[i][0];
                base.Row = bases[i][1];
                spot.Col = destinys[i][0];
                spot.Row = destinys[i][1];

                std::cout<<"Base: "<<base.Col<<" "<<base.Row<<"  Spot: "<<spot.Col<<" "<<spot.Row<<std::endl;
                FindPath(Paintmatrix,Workmatrix,base,spot,true);
            }
        }
        else{
            for (int i = 0; i < 192; ++i){
                PaintSquare(allmidgard,spots[i][1],spots[i][0],red);
                base.Col = bases[i][0];
                base.Row = bases[i][1];
                for (int j = 0; j < 192; ++j){
                    if (doit[(i*192)+j]) {
                        if ((bases[i][0]==spots[j][0]) && (bases[i][1]==spots[j][1])){
                            failspots[failpaths][0] = i;
                            failspots[failpaths][1] = j;
                            failpaths++;
                            continue;
                        }
                        spot.Col = spots[j][0];
                        spot.Row = spots[j][1];

                        long int dist;

                        dist = FindPath(Paintmatrix,Workmatrix,base,spot,false);
                        std::cout<<(i+1)<<" "<<(j+1)<<" "<<dist<<std::endl;

                        dist = FindPath(Paintmatrix,Workmatrix,spot,base,false);
                        std::cout<<(j+1)<<" "<<(i+1)<<" "<<dist<<std::endl;

                        doit[(i*192)+j] = false;
                    }
                    else{
                        continue;
                    }
                }
            }
            for (int i = 0; i < failpaths; ++i){
                base.Col = bases[failspots[i][0]][0];
                base.Row = bases[failspots[i][0]][1];
                spot.Col = spots[failspots[i][1]][0];
                spot.Row = spots[failspots[i][1]][1];

                long int dist;

                dist = FindPath(Paintmatrix,Workmatrix,base,spot,false);
                std::cout<<(failspots[i][0]+1)<<" "<<(failspots[i][1]+1)<<" "<<dist<<std::endl;

                dist = FindPath(Paintmatrix,Workmatrix,spot,base,false);
                std::cout<<(failspots[i][1]+1)<<" "<<(failspots[i][0]+1)<<" "<<dist<<std::endl;
            }
        }
        for (int i = 0; i < 4320; ++i){
            for (int j = 0; j < 7680; ++j){
                if (!Paintmatrix[i][j] ){
                    allmidgard.at<cv::Vec3b>(i,j)[2] = 0;
                    allmidgard.at<cv::Vec3b>(i,j)[1] = 0;
                    allmidgard.at<cv::Vec3b>(i,j)[0] = 0;
                }
                else{
                    if(Paintmatrix[i][j] == 72){
                        allmidgard.at<cv::Vec3b>(i,j)[2] = 72;
                        allmidgard.at<cv::Vec3b>(i,j)[1] = 0;
                        allmidgard.at<cv::Vec3b>(i,j)[0] = 0;
                        if (i*j%64 == 0){
                            cv::imshow( "Path call results so far", allmidgard);
                            cv::waitKey(1);
                        }
                    }
                }
            }
        }
        cv::imshow( "Path call results so far", allmidgard);
        cv::waitKey(0);
        cv::imwrite("allresults.jpg",allmidgard);
    }
}
