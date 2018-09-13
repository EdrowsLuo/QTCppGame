//
// Created by admin on 2018/9/13.
//

#ifndef QT_BB_MYGLBASEVIEW_H
#define QT_BB_MYGLBASEVIEW_H

#include <QtGui/QPainter>
#include "defext.h"
#include "javastyle.h"
#include <string>
//#include <algorithm>


#define SC static const

using namespace std;

namespace mywidget {
    class MW {
        public static int CUSTOM_INDEX;

        public static final int VISIBILITY_SHOW = 1;

        public static final int VISIBILITY_HIDDEN = 2;

        public static final int VISIBILITY_GONE = 3;

        //没有处理事件，事件下发
        public static final int EVENT_FLAG_PASS = 0;

        //处理了事件，但是继续下发，返回值变成true
        public static final int EVENT_FLAG_CHECKING = 1;

        //处理了事件，不继续下发，返回值变成true
        public static final int EVENT_FLAG_HANDLED = 2;

        //处理了事件，处理中产生了拦截
        public static final int EVENT_FLAG_CANCELED = 3;
    };

    int floatToRawIntBits(float size);

    float intBitsToFloat(int size);

    class EdMeasureSpec {
    public static final int SHIFT_SIZE = 32;
    public static final long SIZE_MASK = 4294967295L; //((1UL << SHIFT_SIZE) - 1);
    public static final long MODE_MASK = 12884901888L; //(3UL << SHIFT_SIZE);

    public static final int MODE_NONE = 1;
    public static final int MODE_AT_MOST = 2;
    public static final int MODE_DEFINEDED = 3;

    public static final long LONG_MODE_NONE = 4294967296L; //((long) MODE_NONE) << SHIFT_SIZE;
    public static final long LONG_MODE_AT_MOST = 8589934592L; //((long) MODE_AT_MOST) << SHIFT_SIZE;
    public static final long LONG_MODE_DEFINEDED = 12884901888L;  //((long) MODE_DEFINEDED) << SHIFT_SIZE;

    public static long intToLongMode(int mode) {
            return ((long) mode) << SHIFT_SIZE;
        }

    public static long makeupMeasureSpec(float size, int mode) {
            return intToLongMode(mode) | floatToRawIntBits(size);
        }

    public static float getSize(long spec) {
            return intBitsToFloat((int) (spec & SIZE_MASK));
        }

    public static int getMode(long spec) {
            return (int) ((spec & MODE_MASK) >> SHIFT_SIZE);
        }

    public static long adjustSize(long raw, float add) {
            return makeupMeasureSpec(getSize(raw) + add, getMode(raw));
        }

    public static long setSize(long raw, float size) {
            return makeupMeasureSpec(size, getMode(raw));
        }
    };

    class RectF {
    public static boolean inLTRB(float x, float y, float l, float t, float r, float b) {
            return x >= l && x <= r && y >= t && y <= b;
        }
    };

    class Gravity {
    public static final int VERTICAL_LEFT_BITS = 4;

    public static final int MASK_HORIZON = (1 << VERTICAL_LEFT_BITS) - 1;

    public static final int MASK_VERTICAL = MASK_HORIZON << VERTICAL_LEFT_BITS;

    public static final int LEFT = 1;

    public static final int CENTER_HORIZON = 2;

    public static final int RIGHT = 3;

    public static final int TOP = 1 << VERTICAL_LEFT_BITS;

    public static final int CENTER_VERTICAL = 2 << VERTICAL_LEFT_BITS;

    public static final int BOTTOM = 3 << VERTICAL_LEFT_BITS;

    public static final int None = 0;

    public static final int TopLeft = TOP | LEFT;

    public static final int TopCenter = TOP | CENTER_HORIZON;

    public static final int TopRight = TOP | RIGHT;

    public static final int CenterLeft = CENTER_VERTICAL | LEFT;

    public static final int Center = CENTER_VERTICAL | CENTER_HORIZON;

    public static final int CenterRight = CENTER_VERTICAL | RIGHT;

    public static final int BottomLeft = BOTTOM | LEFT;

    public static final int BottomCenter = BOTTOM | CENTER_HORIZON;

    public static final int BottomRight = BOTTOM | RIGHT;
    };

    class BaseCanvas {
        public int save();
        public void restore();
        public void restoreToCount(int s);
        public BaseCanvas &translate(float dx,float dy);
        public BaseCanvas &clip(float dx,float dy);
        public void setCanvasAlpha(float alpha);
        public float getCanvasAlpha();
    };


    class EdDrawable {
        public Interface(void draw(BaseCanvas &canvas))
    };

    class Param {
    public static final int SHIFT_SIZE = 32;
    public static final long SIZE_MASK = 4294967295L; //(1L << SHIFT_SIZE) - 1;
    public static final long MODE_MASK = 4393751543808L; // ((1L << 10) - 1) << SHIFT_SIZE;

    public static final int NONE = 0;
    public static final int MATCH_PARENT = 1;
    public static final int WRAP_CONTENT = 2;
        //当前方向的父类大小的倍率
    public static final int SCALE_OF_PARENT = 3;
        //另一方向的父类大小的倍率
    public static final int SCALE_OF_PARENT_OTHER = 4;

    public static final int DP = 5;

    public static final long MODE_WRAP_CONTENT = 8589934592L; //((long) WRAP_CONTENT) << SHIFT_SIZE;
    public static final long MODE_MATCH_PARENT = 4294967296L; //((long) MATCH_PARENT) << SHIFT_SIZE;

    public static long intToLongMode(int mode) {
            return ((long) mode) << SHIFT_SIZE;
        }

    public static long makeupScaleOfParentParam(float s) {
            return makeupParam(s, SCALE_OF_PARENT);
        }

    public static long makeupScaleOfParentOtherParam(float s) {
            return makeupParam(s, SCALE_OF_PARENT_OTHER);
        }

    public static long makeupParam(float size) {
            return makeupParam(size, NONE);
        }

    public static long makeupParam(float size, int mode) {
            return intToLongMode(mode) | floatToRawIntBits(size);
        }

    public static float getSize(long param) {
            return intBitsToFloat((int) (param & SIZE_MASK));
        }

    public static int getMode(long param) {
            return (int) ((param & MODE_MASK) >> SHIFT_SIZE);
        }

    public static long adjustSize(long raw, float add) {
            return makeupParam(getSize(raw) + add, getMode(raw));
        }

    public static long setSize(long raw, float size) {
            return makeupParam(size, getMode(raw));
        }
    };

    class EdLayoutParam{
    public long width;
    public long height;
    public float xoffset;
    public float yoffset;
    public EdLayoutParam() {
            width = Param::makeupParam(0, Param::WRAP_CONTENT);
            height = Param::makeupParam(0, Param::WRAP_CONTENT);
        }

    };

    class EdView {
    private EdView *parent;

    private String name;

    //private MContext context;

    protected EdDrawable *background;

    private int visiblility;

    private EdLayoutParam *layoutParam;

    private float measuredWidth, measuredHeight;

    private float minWidth, minHeight;

    private float leftToParent, rightToParent, topToParent, bottomToParent;

    private boolean hasCreatedd;

    private boolean pressed;

    private boolean focus;

        /**
         * 设置是否处理点击事件（事件开始结束均在view范围内，且事件时间不是太久)
         */
    private boolean clickable;

        /**
         * 设置是否处理长摁事件（事件开始结束均在view范围内，且事件时间比较久)
         */
    private boolean longclickable;

        /**
         * 是否接受滚动，包含了两个方向相关的信息。
         * 具体的取值在ScrollEvent.java
         */
    private int scrollableFlag;

    private int gravity;

        /**
         * 用于在完成layout后的动态位置变换
         */
    private float offsetX, offsetY;

    //private AbstractAnimation animation;

    private boolean hasInitialLayouted;

    private boolean outsideTouchable;

    private int initialId;

    //private boolean debug = false;

    private boolean hasSetMeasureDimension;

    public EdView():
        gravity(Gravity::Center),
        longclickable(false),
        hasInitialLayouted(false),
        outsideTouchable(false),
        clickable(false),
        focus(false),
        pressed(false),
        hasCreatedd(false),
        hasSetMeasureDimension(false){

    }

    public EdLayoutParam& getLayoutParam() {
            return *layoutParam;
    }

    public void setLayoutParam(EdLayoutParam &param) {
            this.layoutParam = &param;
    }

    public virtual void onFrameStart() {

    }

    public void setOutsideTouchable(boolean outsideTouchablee) {
            outsideTouchable = outsideTouchablee;
    }

    public boolean isOutsideTouchable() {
            return outsideTouchable;
    }

    public void setOffsetX(float offsetX) {
            this.offsetX = offsetX;
    }

    public void setOffsetY(float offsetY) {
            this.offsetY = offsetY;
        }

    public float getOffsetY() {
            return offsetY;
        }

    public void setGravity(int gravity) {
            this.gravity = gravity;
        }

    public int getGravity() {
            return gravity;
        }

    public boolean isStrictInvalidateLayout() {
            return true;
        }

        /**
     * 如果当前view在滚动，停止滚动
     */
    public void stopScrolling() {

        }

    public void setPressed(boolean pressed) {
            this.pressed = pressed;
        }

    public boolean isPressed() {
            return pressed;
        }
    protected void setScrollableFlag(int scrollableFlag) {
            this.scrollableFlag = scrollableFlag;
        }

    protected int getScrollableFlag() {
            return scrollableFlag;
        }

    public void setLongclickable(boolean longclickable) {
            this.longclickable = longclickable;
        }

    public boolean isLongclickable() {
            return longclickable;
        }

    public void setClickable(boolean clickable) {
            this.clickable = clickable;
        }

    public boolean isClickable() {
            return clickable;
        }

    public boolean hasCreated() {
            return hasCreatedd;
        }

    public float getTop() {
            return topToParent + offsetY;
        }

    public float getBottom() {
            return bottomToParent + offsetY;
        }

    public float getLeft() {
            return leftToParent + offsetX;
        }

    public float getRight() {
            return rightToParent + offsetX;
        }

    public float getWidth() {
            return getRight() - getLeft();
        }

    public float getHeight() {
            return getBottom() - getTop();
        }

    public virtual float getPaddingLeft() {
            return 0;
        }

    public virtual float getPaddingTop() {
            return 0;
        }

    public virtual float getPaddingRight() {
            return 0;
        }

    public virtual float getPaddingBottom() {
            return 0;
        }

    public virtual float getPaddingHorizon() {
            return getPaddingLeft() + getPaddingRight();
        }

    public virtual float getPaddingVertical() {
            return getPaddingTop() + getPaddingBottom();
        }

    public float getMeasuredWidth() {
            return measuredWidth;
        }

    public float getMeasuredHeight() {
            return measuredHeight;
        }
    public void setVisiblility(int visiblility) {
            this.visiblility = visiblility;
        }

    public int getVisiblility() {
            return visiblility;
        }

    public virtual void onCreate() {
            hasCreatedd = true;
        }

    public virtual void performAnimation(double deltaTime) { }

    protected virtual void onDraw(BaseCanvas &canvas) {
            defaultDraw(canvas);
        }

    protected void defaultDraw(BaseCanvas &canvas) {
            drawBackground(canvas);
        }

    protected void drawBackground(BaseCanvas &canvas) {
            if (background != null) {
                int s = canvas.save();
                background->draw(canvas);
                canvas.restoreToCount(s);
            }
        }

    public final void draw(BaseCanvas &canvas) {
            onDraw(canvas);
            /*if (debug) {
                canvas.drawTexture(GLTexture.White, RectF.xywh(0, 0, canvas.getWidth(), canvas.getHeight()), Color4.White, Color4.White, 0.3f);
            }*/
        }

    public static float makeupMeasureSize(float size, long spec) {
            final int specMode = EdMeasureSpec::getMode(spec);
            switch (specMode) {
                case EdMeasureSpec::MODE_AT_MOST:{
                    float sp = EdMeasureSpec::getSize(spec);
                    return size > sp ? sp : size;
                }
                case EdMeasureSpec::MODE_DEFINEDED:
                    return EdMeasureSpec::getSize(spec);
                case EdMeasureSpec::MODE_NONE:
                default:
                    return size;
            }
        }

    public static float getDefaultSize(float size, long spec) {
            float r = size;
            int mode = EdMeasureSpec::getMode(spec);
            switch (mode) {
                case EdMeasureSpec::MODE_NONE:
                    r = size;
                    break;
                case EdMeasureSpec::MODE_DEFINEDED:
                case EdMeasureSpec::MODE_AT_MOST:
                    r = EdMeasureSpec::getSize(spec);
                    break;
            }
            return r;
        }

    protected void setMeasuredDimensition(float w, float h) {
            measuredWidth = w;
            measuredHeight = h;
            hasSetMeasureDimension = true;
        }

    protected virtual void onLayout(boolean changed, float left, float top, float right, float bottom) { }

    protected virtual void onInitialLayouted() {}

    protected final boolean setFrame(float left, float top, float right, float bottom) {
            boolean hasChanged = false;
            if (leftToParent != left || topToParent != top || rightToParent != right || bottomToParent != bottom) {
                hasChanged = true;
                this.leftToParent = left;
                this.topToParent = top;
                this.rightToParent = right;
                this.bottomToParent = bottom;
                if (!hasInitialLayouted) {
                    hasInitialLayouted = true;
                    onInitialLayouted();
                }
            }
            return hasChanged;
        }

    public virtual void layout(float left, float top, float right, float bottom) {
            boolean hasChanged = setFrame(left, top, right, bottom);
            if (hasChanged) {
                onLayout(true, left, top, right, bottom);
            } else {
                if (isStrictInvalidateLayout()) {
                    onLayout(false, left, top, right, bottom);
                }
            }
        }

    public boolean inViewBound(float x, float y) {
            return RectF::inLTRB(x, y, getLeft(), getTop(), getRight(), getBottom());
        }

    };
}



#endif //QT_BB_MYGLBASEVIEW_H
