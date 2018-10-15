/*
 Copyright (C) 2016 Stephen Braitsch [http://braitsch.io]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */


#include "ofxSmartFontUC.h"

using namespace std;

vector<shared_ptr<ofxSmartFontUC>> ofxSmartFontUC::mFonts;

/*
 instance methods
 */

void ofxSmartFontUC::draw(string s, int x, int y)
{
    drawString(s, x, y);
}

string ofxSmartFontUC::name()
{
    return mName;
}

void ofxSmartFontUC::name(string name)
{
    mName = name;
}

string ofxSmartFontUC::file()
{
    return mFile;
}

int ofxSmartFontUC::size()
{
    return mSize;
}

ofRectangle ofxSmartFontUC::rect(string s, int x, int y)
{
    return getStringBoundingBox(s, x, y);
}

float ofxSmartFontUC::width(string s, int x, int y)
{
    return getStringBoundingBox(s, x, y).width;
}

float ofxSmartFontUC::height(string s, int x, int y)
{
    return getStringBoundingBox(s, x, y).height;
}

/*
 static methods
 */

shared_ptr<ofxSmartFontUC> ofxSmartFontUC::add(string file, int size, string name)
{
    for(auto f:mFonts){
        if (f->file()==file && f->size()==size){
            log(f->name() + "@ pt size "+std::to_string(f->size()) + " is already in memory.");
            return f;
        }
    }
    struct make_shared_sf : public ofxSmartFontUC {
        make_shared_sf(string file, int size, string name) : ofxSmartFontUC(file, size, name){}
    };
    mFonts.push_back(make_shared<make_shared_sf>(file, size, name));
    return mFonts.back();
}

shared_ptr<ofxSmartFontUC> ofxSmartFontUC::get(string name)
{
    for(auto f:mFonts){
        if (f->name()==name) return f;
    }
    log("requested font : "+ name + " not found");
    return nullptr;
}

shared_ptr<ofxSmartFontUC> ofxSmartFontUC::get(string name, int size)
{
    for(auto f:mFonts){
        if (f->file().find(name) != std::string::npos && f->size()==size){
            return f;
        }
    }
    log("requested font : "+ name +" @ " +std::to_string(size)+ " not found");
    return nullptr;
}

shared_ptr<ofxSmartFontUC> ofxSmartFontUC::get(vector<string> keys, int size)
{
    for(auto f:mFonts){
        bool match = true;
        for(auto k:keys){
            if (ofToLower(f->file()).find(ofToLower(k)) == std::string::npos) match = false;
        }
        if (match && f->size()==size) return f;
    }
    std::stringstream ss;
    for(int i=0; i<keys.size(); i++){
        ss << keys[i];
        if (i<keys.size()-1) ss << ",";
    }
    log("nothing found in search for : "+ ss.str() +" @ " +std::to_string(size)+ "pt");
    return nullptr;
}

void ofxSmartFontUC::list()
{
    log("----------------------------------");
    log("total # of fonts cached = " + std::to_string(mFonts.size()));
    for(auto f:mFonts){
        log(f->name() + " (" + std::to_string(f->size()) +"pt -> "+f->file()+")");
    }
    log("----------------------------------");
}

void ofxSmartFontUC::log(string msg)
{
    cout << "ofxSmartFontUC :: "<< msg << endl;
}

