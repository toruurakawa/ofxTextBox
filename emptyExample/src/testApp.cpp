#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(255);
    font.loadFont("Osaka.ttf", 12);
    
    tb_en.loadFont("Osaka.ttf", 12);
    tb_en.setText("How happy I am that I am gone! My dear friend, what a thing is the heart of man! To leave you, from whom I have been inseparable, whom I love so dearly, and yet to feel happy! I know you will forgive me. Have  other attachments been specially appointed by fate to torment a head like mine? Poor Leonora! and yet I was not to blame. Was it my fault, that, whilst the peculiar charms of her sister afforded me an agreeable entertainment, a passion for me was engendered in her feeble heart? And yet am I wholly blameless? Did I not encourage her emotions? Did I not feel charmed at those truly genuine expressions of nature, which, though but little mirthful in reality, so often amused us? ");
    tb_en.setRectangle(ofRectangle(100,100,300,200));
    
    tb_jp.loadFont("Osaka.ttf", 12);
    tb_jp.setText("自分が中学の四年生だった時の話である。その年の秋、日光から足尾へかけて、三泊の修学旅行があった。「午前六時三十分上野停車場前集合、同五十分発車……」こう云う箇条が、学校から渡す謄写版の刷物に書いてある。当日になると自分は、碌に朝飯も食わずに家をとび出した。電車でゆけば停車場まで二十分とはかからない。――そう思いながらも、何となく心がせく。停車場の赤い柱の前に立って、電車を待っているうちも、気が気でない。");
    tb_jp.setRectangle(ofRectangle(500,100,300,200));
    
    tb_resize.loadFont("Osaka.ttf", 12);
    tb_resize.setText("自分が中学の四年生だった時の話である。");
    tb_resize.setRectangle(ofRectangle(250, 350, 300, 250));
    tb_resize.setAutoResizeFontSize(true);

}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(0);
    tb_en.draw();
    tb_jp.draw();
    tb_resize.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}