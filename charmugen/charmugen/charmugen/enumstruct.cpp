#include "enumstruct.h"

bool iscollapse(Collapsebox* a, Collapsebox* b){
	bool collapsex=false, collapsey=false;
	if(a->up==-1||b->up==-1)
		return false;
	if(a->down>b->down){
		if(a->up<b->down)
			collapsey=true;
	}
	else{
		if(b->up<a->down)
			collapsey=true;
	}
	if(a->right>b->right){
		if(a->left<b->right)
			collapsex=true;
	}
	else{
		if(b->left<a->right)
			collapsex=true;
	}
	return collapsex&&collapsey;
}