//
// Created by admin on 2018/9/13.
//

#ifndef QT_BB_EDABSTRACTVIEWGROUP_H
#define QT_BB_EDABSTRACTVIEWGROUP_H

#define extends(cl) p_ublic cl
#include "MyGLBaseView.h"
#include "javastyle.h"


namespace mywidget {
#undef public
    class EdAbstractViewGroup : public EdView{
#define public public:
    private boolean backwardsDraw;

    private float paddingLeft, paddingTop, paddingRight, paddingBottom;

    private float alpha;

    protected vector<EdView*> children;

    public EdAbstractViewGroup():
        EdView(),
        backwardsDraw(false),
        alpha(1){

        }

    protected virtual void onLayout(boolean changed, float left, float top, float right, float bottom) = 0;

    protected virtual void onMeasure(long widthSpec, long heightSpec) = 0;

    public void setBackwardsDraw(boolean backwardsDraw) {
            this.backwardsDraw = backwardsDraw;
        }

    public boolean isBackwardsDraw() {
            return backwardsDraw;
        }

    public void setPaddingLeft(float paddingLeft) {
            this.paddingLeft = paddingLeft;
        }

    public float getAlpha() {
            return alpha;
        }

    public void setAlpha(float alpha) {
            this.alpha = alpha;
        }

    public EdView& getChildAt(int i) {
        return *children[i];
    }

    public int getChildrenCount() {
        return children.size();
    }

    public virtual void onFrameStart() {
            EdView::onFrameStart();
            final int count = getChildrenCount();
            for (int i = 0; i < count; i++) {
                EdView &view = getChildAt(i);
                if (view.getVisiblility() != MW::VISIBILITY_GONE) {
                    view.onFrameStart();
                }
            }
        }

    public virtual void performAnimation(double deltaTime) {
            EdView::performAnimation(deltaTime);
            final int count = getChildrenCount();
            for (int i = 0; i < count; i++) {
                EdView &view = getChildAt(i);
                if (view.getVisiblility() != MW::VISIBILITY_GONE) {
                    view.performAnimation(deltaTime);
                }
            }
        }

    protected virtual void dispatchDraw(BaseCanvas &canvas) {
            final int count = getChildrenCount();
            if (backwardsDraw) {
                for (int i = count - 1; i >= 0; i--) {
                    EdView &view = getChildAt(i);
                    if (view.getVisiblility() == MW::VISIBILITY_SHOW) {
                        final int savedcount = canvas.save();
                        canvas.translate(view.getLeft(), view.getTop());
                        canvas.clip(view.getWidth(), view.getHeight());
                        view.draw(canvas);
                        canvas.restoreToCount(savedcount);
                    }
                }
            } else {
                for (int i = 0; i < count; i++) {
                    EdView &view = getChildAt(i);
                    if (view.getVisiblility() == MW::VISIBILITY_SHOW) {
                        final int savedcount = canvas.save();
                        canvas.translate(view.getLeft(), view.getTop());
                        canvas.clip(view.getWidth(), view.getHeight());
                        view.draw(canvas);
                        canvas.restoreToCount(savedcount);
                    }
                }
            }
        }

    protected virtual void onDraw(BaseCanvas &canvas) {
            canvas.save();
            canvas.setCanvasAlpha(canvas.getCanvasAlpha() * getAlpha());
            drawBackground(canvas);
            dispatchDraw(canvas);
            canvas.restore();
        }

    protected virtual void layoutChildren(float left, float top, float right, float bottom) {
            int count = getChildrenCount();
            float parentLeft = getPaddingLeft();
            float parentTop = getPaddingTop();

            for (int i = 0; i < count; i++) {
                EdView &view = getChildAt(i);
                if (view.getVisiblility() != MW::VISIBILITY_GONE) {
                    EdLayoutParam &param = view.getLayoutParam();
                    float dx = param.xoffset + parentLeft;
                    float dy = param.yoffset + parentTop;
                    view.layout(dx, dy, view.getMeasuredWidth() + dx, view.getMeasuredHeight() + dy);
                }
            }
        }

    public void addView(EdView &view, EdLayoutParam &param) {
            view.setLayoutParam(param);
            children.push_back(&view);
        }
    };
}



#endif //QT_BB_EDABSTRACTVIEWGROUP_H
