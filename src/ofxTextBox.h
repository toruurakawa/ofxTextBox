//
//  ofxTextBox.h
//
//  Created by TORU URAKAWA on 2012/10/12.
//
//

#pragma once 

#include "ofMain.h"

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
#ifdef TARGET_OSX
		_text = toWstring(text);
#else
		_text = util::ofxTrueTypeFontUC::convToWString(text);
#endif
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
#ifdef TARGET_OSX
			while (_font.getStringBoundingBox(toString(_drawingText),0,0).height > _rect.height){
#else
            while (_font.getStringBoundingBox(_drawingText,0,0).height > _rect.height){
#endif
                _drawingText = _drawingText.substr(0, _drawingText.length()-1);
                _bOmitted = true;
            }
        }
        
        if (_bAutoResizeFontSize) {
            int size = 10;
            while (!_bOmitted) {
                _font.loadFont(_fontName, _fontSize++);
                reconstructText();
#ifdef TARGET_OSX
				if (_font.getStringBoundingBox(toString(_drawingText),0,0).height + 20 >= _rect.height){
#else
                if (_font.getStringBoundingBox(_drawingText,0,0).height + 20 >= _rect.height){
#endif
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
#ifdef TARGET_OSX
			_font.drawString(toString(_drawingText), _rect.x-_rect.width/2., _rect.y-_rect.height/2.);
#else
            _font.drawString(_drawingText, _rect.x-_rect.width/2., _rect.y-_rect.height/2.);
#endif
        } else
#ifdef TARGET_OSX
			_font.drawString(toString(_drawingText), _rect.x, _rect.y);
#else
            _font.drawString(_drawingText, _rect.x, _rect.y);
#endif
        if (_bShowFrame) {
            ofPushStyle();
            ofNoFill();
            ofDrawRectangle(_rect.x, _rect.y, _rect.width, _rect.height);
            ofPopStyle();
        }
    }
    
    void reconstructText(){
        _drawingText = _text;
        _drawingText.insert(0, L"\n");
#ifdef TARGET_OSX
		 ofRectangle r = _font.getStringBoundingBox(toString(_text), _rect.x, _rect.y);
#else
        ofRectangle r = _font.getStringBoundingBox(_text, _rect.x, _rect.y);
#endif
        if (r.width > _rect.width || r.height > _rect.height) {
            int i = 0;
            wstring s_left = _text.substr(1);
#ifdef TARGET_OSX
			while (_font.getStringBoundingBox(toString(s_left), 0, 0).width > _rect.width) {
#else
            while (_font.getStringBoundingBox(s_left, 0, 0).width > _rect.width) {
#endif
                wstring tmp_s = L"";
                int j = 0;
#ifdef TARGET_OSX
				while (_font.getStringBoundingBox(toString(tmp_s),0,0).width < _rect.width) {
#else
                while (_font.getStringBoundingBox(tmp_s,0,0).width < _rect.width) {
#endif
                    tmp_s = _drawingText.substr(i,j);
                    j++;
                }
                i += j-1;
                _drawingText.insert(i-1, L"\n");
                s_left = _drawingText.substr(i);
            }
        }
    }
	
	ofRectangle& getRect(){
		return _rect;
	}


#ifdef TARGET_OSX
	const string toString(wstring _s){
		const std::string tmpString( _s.begin(), _s.end() );
		return tmpString;
	}
	const wstring toWstring(string _s){
		const std::wstring tmpString( _s.begin(), _s.end() );
		return tmpString;
	}
#endif
    
    
protected:
    wstring                     _drawingText;
    wstring                     _text;
    string                      _fontName;
    int                         _fontSize;
    ofRectangle                 _rect;
    ofTrueTypeFont              _font;
    bool                        _bShowFrame;
    bool                        _bAutoResizeFontSize;
    bool                        _bOmitted;

};
