//
//  Block.cpp
//  DontTouchWhiteBlock
//
//  Created by ZhiyangSong on 6/18/14.
//
//

#include "Block.h"
Vector<Block*>* Block::blocks=new Vector<Block*>();

Block* Block::createWithArgs(Color3B color,Size size,string lable,float
                              fontSize,Color4B textColor){
    auto block = new Block();
    
    block->initWithArgs(color , size, lable, fontSize, textColor);
    
    block->autorelease();
    
    blocks -> pushBack(block);
    
    return block;
}
bool Block::initWithArgs(Color3B color,Size size,string lable,float
                         fontSize,Color4B textColor){
    Sprite::init();
    
    setContentSize(size);
    
    setAnchorPoint(Point::ZERO);
    
    setTextureRect(Rect(0,0,size.width,size.height));
    
    setColor(color);
    
    auto l = Label::create();
    
    l->setString(lable);
    
    l->setSystemFontSize(fontSize);

    
    addChild(l);
    
    l->setPosition(size.width/2,size.height/2);
    
    return true;
}
void Block::removeBlock()
{
    removeFromParent();
    blocks->eraseObject(this);
}
