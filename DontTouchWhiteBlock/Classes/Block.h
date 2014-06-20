//
//  Block.h
//  DontTouchWhiteBlock
//
//  Created by ZhiyangSong on 6/18/14.
//
//

#ifndef __DontTouchWhiteBlock__Block__
#define __DontTouchWhiteBlock__Block__

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;
using namespace std;
class Block: public Sprite{
private:
    static Vector<Block*>* blocks;
    
    int lineIndex;
    
public:
    static Vector<Block*>* getBlocks(){
        return blocks;
    }
    
    static Block* createWithArgs(Color3B color,Size size,string lable,float
                                 fontSize,Color4B textColor);
    virtual bool initWithArgs(Color3B color,Size size,string lable,float
                              fontSize,Color4B textColor);
    
    void removeBlock();
    
    int getLineIndex(){
        return lineIndex;
    }
    
    void setLineIndex(int index){
        lineIndex = index;
    }
    
    void moveDown(){
        this->lineIndex--;
        Size size = Director::getInstance()->getVisibleSize();
        
        runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(),lineIndex*size.height/4)),CallFunc::create([this](){
            if(this->lineIndex<0 ){
                this-> removeBlock();
            }
        }),NULL));
        
    }
};
#endif /* defined(__DontTouchWhiteBlock__Block__) */
