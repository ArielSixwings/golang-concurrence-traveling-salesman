package rgbacolor

const LightPink = 0

const Fuchsia = 1

const Purple = 2

const LightPurple = 3

const Navy = 4

const DeeoBlue = 5

const Blue = 6

const GrayBlue = 7

const MediumBlue = 8

const DarkBlue = 9

const WhiteBlue = 10

const GrayLightBlue = 11

const Aqua = 12

const Teal = 13

const LightBlue = 14

const WhiteGreen = 15

const BlueGreen = 16

const Lime = 17

const Green = 18

const DarkGreen = 19

const BabyBlue = 20

const LightGreen = 21

const Yellow = 22

const Olive = 23

const MossGreen = 24

const PaleYellow = 25

const StrongYellow = 26

const BurntYellow = 27

const PaleOrange = 28

const Orange = 29

const Brown = 30

const Red = 31

const Maroon = 32

const White = 33

const Silvere = 34

const LightGray = 35

const Gray = 36

const DarkGray = 37

const Black = 38

const HotPink = 39

/**
 * @brief      Class for rgba color.
 */
type RGBAcolor struct {
    Red   uint8
    Green uint8
    Blue  uint8
    label string
}

/**
 * @brief      Sets the color.
 *
 * @param      color  The color
 * @param      index  The index
 *
 * @return     { A chanel, Red, Green or Blue}
 */
func SetColor(color int, index int) uint8 {

    Colors := []RGBAcolor{

        {label: "LightPink", Red: 255, Green: 153, Blue: 204},

        {label: "Fuchsia", Red: 255, Green: 0, Blue: 255},

        {label: "Purple", Red: 128, Green: 0, Blue: 128},

        {label: "Navy", Red: 0, Green: 0, Blue: 128},

        {label: "DeeoBlue", Red: 51, Green: 51, Blue: 153},

        {label: "GrayBlue", Red: 102, Green: 102, Blue: 153},

        {label: "Blue", Red: 0, Green: 0, Blue: 255},

        {label: "MediumBlue", Red: 51, Green: 102, Blue: 255},

        {label: "DarkBlue", Red: 0, Green: 51, Blue: 102},

        {label: "WhiteBlue", Red: 153, Green: 204, Blue: 255},

        {label: "GrayLightBlue", Red: 0, Green: 204, Blue: 255},

        {label: "Aqua", Red: 0, Green: 255, Blue: 255},

        {label: "Teal", Red: 0, Green: 128, Blue: 128},

        {label: "LightBlue", Red: 51, Green: 204, Blue: 204},

        {label: "WhiteGreen", Red: 204, Green: 255, Blue: 255},

        {label: "BabyBlue", Red: 51, Green: 153, Blue: 102},

        {label: "Lime", Red: 0, Green: 255, Blue: 0},

        {label: "Green", Red: 0, Green: 128, Blue: 0},

        {label: "Darkgrey", Red: 0, Green: 51, Blue: 0},

        {label: "BabyBlue", Red: 204, Green: 255, Blue: 204},

        {label: "LightGreen", Red: 153, Green: 204, Blue: 0},

        {label: "Yellow", Red: 255, Green: 255, Blue: 0},

        {label: "Olive", Red: 128, Green: 128, Blue: 0},

        {label: "MossGreen", Red: 51, Green: 51, Blue: 0},

        {label: "PaleYellow", Red: 255, Green: 255, Blue: 153},

        {label: "StrongYellow", Red: 255, Green: 204, Blue: 0},

        {label: "BurntYellow", Red: 255, Green: 153, Blue: 0},

        {label: "PaleOrange", Red: 255, Green: 204, Blue: 153},

        {label: "Orange", Red: 255, Green: 102, Blue: 0},

        {label: "Brown", Red: 153, Green: 51, Blue: 0},

        {label: "Red", Red: 255, Green: 0, Blue: 0},

        {label: "Maroon", Red: 128, Green: 0, Blue: 0},

        {label: "White", Red: 255, Green: 255, Blue: 255},

        {label: "Silver", Red: 192, Green: 192, Blue: 192},

        {label: "LightGray", Red: 150, Green: 150, Blue: 150},

        {label: "Gray", Red: 128, Green: 128, Blue: 128},

        {label: "Darkgrey", Red: 51, Green: 51, Blue: 51},

        {label: "Black", Red: 0, Green: 0, Blue: 0},

        {label: "HardPink", Red: 153, Green: 51, Blue: 102},
    }
    if index == 0 {
        return Colors[color].Red
    }
    if index == 1 {
        return Colors[color].Green
    }
    if index == 2 {
        return Colors[color].Blue
    }
    return 10
}
