package android.support.v7.widget;

import android.graphics.Canvas;
import android.graphics.ColorFilter;
import android.graphics.Outline;
import android.graphics.drawable.Drawable;
import android.support.annotation.NonNull;
import android.support.annotation.RequiresApi;

/* loaded from: classes.dex */
class ActionBarBackgroundDrawable extends Drawable {
    final ActionBarContainer mContainer;

    @Override // android.graphics.drawable.Drawable
    public int getOpacity() {
        return 0;
    }

    @Override // android.graphics.drawable.Drawable
    public void setAlpha(int i) {
    }

    @Override // android.graphics.drawable.Drawable
    public void setColorFilter(ColorFilter colorFilter) {
    }

    public ActionBarBackgroundDrawable(ActionBarContainer actionBarContainer) {
        this.mContainer = actionBarContainer;
    }

    @Override // android.graphics.drawable.Drawable
    public void draw(Canvas canvas) {
        if (this.mContainer.mIsSplit) {
            if (this.mContainer.mSplitBackground == null) {
                return;
            }
            this.mContainer.mSplitBackground.draw(canvas);
            return;
        }
        if (this.mContainer.mBackground != null) {
            this.mContainer.mBackground.draw(canvas);
        }
        if (this.mContainer.mStackedBackground == null || !this.mContainer.mIsStacked) {
            return;
        }
        this.mContainer.mStackedBackground.draw(canvas);
    }

    @Override // android.graphics.drawable.Drawable
    @RequiresApi(21)
    public void getOutline(@NonNull Outline outline) {
        if (this.mContainer.mIsSplit) {
            if (this.mContainer.mSplitBackground == null) {
                return;
            }
            this.mContainer.mSplitBackground.getOutline(outline);
        } else if (this.mContainer.mBackground == null) {
        } else {
            this.mContainer.mBackground.getOutline(outline);
        }
    }
}