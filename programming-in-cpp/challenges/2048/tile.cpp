/*
 * File: tile.cpp
 * Author: Daniel Carter
 * Date: 20-11-2019
 * Desc:The implementation of all the tile class function definitions
 * Copyright: University of West of England 2017
 */

#include "tile.hpp"

//Getter & Setter for the tile value 
void Tile::setContents(int contents) {
        contents_= contents;
}

int Tile::getContents() {
        return contents_;
}

//Getter & Setters for all RGB tile specific values
void Tile::setR(int r) {
    r_ = r;
}

int Tile::getR() {
    int r = r_;
    return r;
}

void Tile::setG(int g) {
    g_ = g;
}

int Tile::getG() {
    int g = g_;
    return g;
}

void Tile::setB(int b) {
    b_ = b;
}

int Tile::getB() {
    int b = b_;
    return b;
}

//Getter & Setters for translating the value to a string
void Tile::setText(string text) {
    text_ = text;
}

string Tile::getText() {
    string text = text_;
    return text;
}