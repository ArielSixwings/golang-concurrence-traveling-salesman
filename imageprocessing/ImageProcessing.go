package imageprocessing

import (
    "gocv.io/x/gocv"
)

func ProcessImage(GrayImage gocv.Mat, Histogram gocv.Mat, Menssage string, show bool, save bool) gocv.Mat {

    gocv.EqualizeHist(GrayImage, &Histogram) //perform the histogram

    if show {
        ShowImage("The histogram was done!", Histogram, 0)
    }
    if save {
        SaveImage(Menssage, Histogram)
    }

    return Histogram
}
