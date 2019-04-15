package imageprocessing

import (
    "gocv.io/x/gocv"
    "image"
    "image/color"
)

func PaintCircle(Image gocv.Mat, center image.Point, radius int, color color.RGBA, thickness int, show bool, save bool) {
    gocv.Circle(&Image, center, radius, color, thickness)

    //func Circle(img *Mat, center image.Point, radius int, c color.RGBA := color.RGBA, thickness int)

    if show {
        ShowImage("The Circle was done!", Image, 0)
    }

    if save {
        SaveImage("CircleMade", Image)
    }
}

func PaintRectangle(Image gocv.Mat, r image.Rectangle, color color.RGBA, thickness int, show bool, save bool) {

    gocv.Rectangle(&Image, r, color, thickness)

    if show {
        ShowImage("The Rectangle was done!", Image, 0)
    }

    if save {
        SaveImage("RectangleMade", Image)
    }
}
