package imageprocessing

import (
    "gocv.io/x/gocv"
)

func ProceedCanny(ImageHistogram gocv.Mat, Menssage string, show bool, save bool) gocv.Mat {

    //variables
    var threshold_low float32 = 750
    var threshold_high float32 = 900
    //

    ImagesEdges := gocv.NewMat()

    gocv.Canny(ImageHistogram, &ImagesEdges, threshold_low, threshold_high)

    if show {
        ShowImage("The Canne was done!", ImagesEdges, 0)
    }
    if save {
        SaveImage(Menssage, ImagesEdges)
    }

    return ImagesEdges
}
