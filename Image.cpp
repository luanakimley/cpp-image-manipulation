//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"

using namespace std;

bool Image::load(string filename)
{
    ifstream ifs;
    ifs.open(filename, ios::binary);
    // need to spec. binary mode for Windows users


    if (ifs.fail()) {
        return false;
    }

    string header;
    int width, height, b;
    ifs >> header;
    if (strcmp(header.c_str(), "P6") != 0) return false;
    ifs >> width >> height >> b;

    this->w = width;
    this->h = height;
    this->pixels = new Rgb[width * height]; // this is throw an exception if bad_alloc
    ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data
    unsigned char pix[3]; // read each pixel one by one and convert bytes to floats
    for (int i = 0; i < width * height; ++i) {
        ifs.read(reinterpret_cast<char *>(pix), 3);
        this->pixels[i].r = pix[0];
        this->pixels[i].g = pix[1];
        this->pixels[i].b = pix[2];
    }
    ifs.close();

    return true;
}
bool Image::loadRaw(string filename)
{
    ifstream in(filename);
    if(in.good())
    {
        in >> w >> h;

        for(int i=0; i< w*h; i++)
        {
            float r, g, b;
            in >> r >> g >> b;
            this->pixels[i].r = (unsigned char) (r * 255);
            this->pixels[i].g = (unsigned char) (g * 255);
            this->pixels[i].b = (unsigned char) (b * 255);

        }

        in.close();

        return true;
    }
    return false;
}
bool Image::savePPM(string filename)
{
    if(this->w == 0 || this-> h == 0) return false;

    ofstream ofs;

    ofs.open(filename, ios::binary);

    if(ofs.fail()) return false;

    ofs << "P6\n" << this->w << " " << this->h << "\n255\n";

    unsigned char r, g, b;

    for (int i=0; i< this->w * this->h; i++)
    {
        r = this->pixels[i].r;
        g = this->pixels[i].g;
        b = this->pixels[i].b;
        ofs << r << g << b;
    }

    ofs.close();

    return true;
}


void Image::filterRed()
{
    for(int i=0; i < this->w * this-> h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}

void Image::filterGreen()
{
    for(int i=0; i < this->w * this-> h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for(int i=0; i < this->w * this-> h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].r = 0;
    }
}
void Image::greyScale()
{
    for(int i=0; i < this->w * this-> h; i++)
    {
        float y = (0.2126 * this->pixels[i].r) + (0.7152 * this->pixels[i].g) + (0.0722 * this->pixels[i].b);
        this->pixels[i].r = this->pixels[i].g = this->pixels[i].b = y;
    }
}
void Image::flipHorizontal()
{
    for(int x=0; x < this->h; x++)
    {
        for (int y=0; y < this->w/2; y++)
        {
            swap(this->pixels[(x * w + y)], this->pixels[(x * w + (w - y))]);
        }
    }
}
void Image::flipVertically()
{
    for(int x=0; x < this->w; x++)
    {
        for (int y=0; y < this->h/2; y++)
        {
            swap(this->pixels[(x + y * w)], this->pixels[(x + (h - 1 - y) * w)]);
        }
    }
}
void Image::AdditionalFunction1()
{

}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}