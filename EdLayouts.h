//
// Created by admin on 2018/9/13.
//

#ifndef QT_BB_EDLAYOUTS_H
#define QT_BB_EDLAYOUTS_H

#include "EdAbstractViewGroup.h"
#include "javastyle.h"
#include "jmath.h"

using namespace javastyle;

namespace mywidget {
    class AbsoluteLayout: EdAbstractViewGroup {
    protected virtual void onLayout(boolean changed, float left, float top, float right, float bottom) {
            layoutChildren(left, top, right, bottom);
        }

    protected void onMeasure(long widthSpec, long heightSpec) {

            //EdAbstractViewGroup::measureChildren(widthSpec, heightSpec);
            float xd;
            float yd;
            {
                int mode = EdMeasureSpec::getMode(widthSpec);
                switch (mode) {
                    case EdMeasureSpec::MODE_DEFINEDED:
                        xd = EdMeasureSpec::getSize(widthSpec) + getPaddingHorizon();
                        break;
                    case EdMeasureSpec::MODE_AT_MOST:
                        //xd = jmath::min(EdMeasureSpec::getSize(widthSpec), getPaddingHorizon() + getDefaultMaxChildrenMeasuredWidth());
                        break;
                    case EdMeasureSpec::MODE_NONE:
                    default:
                        //xd = getPaddingHorizon() + getDefaultMaxChildrenMeasuredWidth();
                        break;
                }
            }
            /*{
                final int mode = EdMeasureSpec.getMode(heightSpec);
                switch (mode) {
                    case EdMeasureSpec.MODE_DEFINEDED:
                        yd = getPaddingVertical() + EdMeasureSpec.getSize(heightSpec);
                        break;
                    case EdMeasureSpec.MODE_AT_MOST:
                        yd = Math.min(EdMeasureSpec.getSize(heightSpec), getPaddingVertical() + getDefaultMaxChildrenMeasuredHeight());
                        break;
                    case EdMeasureSpec.MODE_NONE:
                    default:
                        yd = getPaddingVertical() + getDefaultMaxChildrenMeasuredHeight();
                        break;
                }
            }
            setMeasuredDimensition(xd, yd);*/
        }
    };
}



#endif //QT_BB_EDLAYOUTS_H
