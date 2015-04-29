//
//  ofxTextBox.h
//
//  Created by TORU URAKAWA on 2012/10/12.
//
//

#pragma once 

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class ofxTextBox
{
public:
    ofxTextBox()
    {
        _text  = L"";
        _bShowFrame = true;
        _bAutoResizeFontSize = false;
        _bOmitted = false;
    }
    
    virtual ~ofxTextBox()
    {
        _text  = L"";
    }
    
    void setText(string text)
    {
        _text = util::ofxTrueTypeFontUC::convToWString(text);
        refresh();
    }
    
    void setRectangle(ofRectangle rect)
    {
        _rect = rect;
        refresh();
    }
    
    void loadFont(string name, int size)
    {
        _fontName = name;
        _fontSize = size;
        _font.loadFont(_fontName, _fontSize);
        refresh();
    }
    
    void showsFrame(bool b){
        _bShowFrame = b;
    }
    
    void setAutoResizeFontSize(bool b){
        _bAutoResizeFontSize = b;
        refresh();
    }
    
    void refresh()
    {
        if (_text.c_str() != NULL && _rect.width > 0 && _rect.height > 0 ){
            reconstructText();
            while (_font.getStringBoundingBox(_drawingText,0,0).height > _rect.height){
                _drawingText = _drawingText.substr(0, _drawingText.length()-1);
                _bOmitted = true;
            }
        }
        
        if (_bAutoResizeFontSize) {
            int size = 10;
            while (!_bOmitted) {
                _font.loadFont(_fontName, _fontSize++);
                reconstructText();
                if (_font.getStringBoundingBox(_drawingText,0,0).height + 20 >= _rect.height){
                    _font.loadFont(_fontName, --_fontSize);
                    reconstructText();
                    _bOmitted = true;
                }
            }
        }
    }
    
    void draw()
    {
        if (ofGetRectMode() == OF_RECTMODE_CENTER) {
            _font.drawString(_drawingText, _rect.x-_rect.width/2., _rect.y-_rect.height/2.);
        } else
            _font.drawString(_drawingText, _rect.x, _rect.y);
        if (_bShowFrame) {
            ofPushStyle();
            ofNoFill();
            ofRect(_rect.x, _rect.y, _rect.width, _rect.height);
            ofPopStyle();
        }
    }
    
    void reconstructText(){
        _drawingText = _text;
        _drawingText.insert(0, L"\n");
        ofRectangle r = _font.getStringBoundingBox(_text, _rect.x, _rect.y);
        if (r.width > _rect.width || r.height > _rect.height) {
            int i = 0;
            wstring s_left = _text.substr(1);
            while (_font.getStringBoundingBox(s_left, 0, 0).width > _rect.width) {
                wstring tmp_s = L"";
                int j = 0;
                while (_font.getStringBoundingBox(tmp_s,0,0).width < _rect.width) {
                    tmp_s = _drawingText.substr(i,j);
                    j++;
                }
                i += j-1;
                _drawingText.insert(i-1, L"\n");
                s_left = _drawingText.substr(i);
            }
        }
    }
    
    
protected:
    wstring                     _drawingText;
    wstring                     _text;
    string                      _fontName;
    int                         _fontSize;
    ofRectangle                 _rect;
    ofxTrueTypeFontUC           _font;
    bool                        _bShowFrame;
    bool                        _bAutoResizeFontSize;
    bool                        _bOmitted;

};
