package main

import (
	"code.google.com/p/go-tour/pic"
	"image"
	"image/color"
)

// Image interface:
// 
// type Image interface {
// 	ColorModel() color.Model
// 	Bounds() Rectangle
// 	At(x, y int) color.Color
// }
// 
type Image struct{
	w, h int
	colour uint8
}

func (img *Image) ColorModel() color.Model {
	return color.RGBAModel
}

func (img *Image) Bounds() image.Rectangle {
	return image.Rect(0, 0, img.w, img.h)
}

func (img *Image) At(x, y int) color.Color {
	return color.RGBA{img.colour+uint8(x), img.colour+uint8(y), 255, 255}
}

func main() {
	m := Image{100, 100, 50}
	pic.ShowImage(&m)
}
