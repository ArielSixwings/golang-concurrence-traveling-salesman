package main

import (
    "./imageprocessing"
    "gocv.io/x/gocv"
)

/**
 *
 * @brief      { function_description }
 * @return     { description_of_the_return_value }
 */
func main() {
    names := []string{
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
        "./regions/region23.jpg"}

    histnames := []string{
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
        "./regions/hist/histregion23.jpg"}

    Midgardhist := gocv.NewMat() //mat for histogram equalization
    regionhist := gocv.NewMat()
    grayregion := gocv.NewMat()
    Midgardgray := gocv.NewMat() //mat for read
    Midgard := gocv.NewMat()     //mat for paint

    Midgardgray = imageprocessing.ReadImage(Midgardgray, "./imageprocessing/Images/midgard.jpg", true, false, false)
    Midgard = imageprocessing.ReadImage(Midgard, "./imageprocessing/Images/midgard.jpg", true, true, true)

    Midgardhist = imageprocessing.ProcessImage(Midgardgray, Midgardhist, "./imageprocessing/Images/midgardhist.jpg", true, true)
    for i := 0; i < 24; i++ {
        grayregion = imageprocessing.ReadImage(grayregion, names[i], true, false, false)
        regionhist = imageprocessing.ProcessImage(grayregion, regionhist, histnames[i], true, true)
    }

}
