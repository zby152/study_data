package android.support.v4.view;

import android.os.Build;
import android.support.annotation.NonNull;
import android.support.compat.R;
import android.view.View;
import android.view.ViewGroup;
import android.view.accessibility.AccessibilityEvent;

/* loaded from: classes.dex */
public final class ViewGroupCompat {
    public static final int LAYOUT_MODE_CLIP_BOUNDS = 0;
    public static final int LAYOUT_MODE_OPTICAL_BOUNDS = 1;

    private ViewGroupCompat() {
    }

    @Deprecated
    public static boolean onRequestSendAccessibilityEvent(ViewGroup viewGroup, View view, AccessibilityEvent accessibilityEvent) {
        return viewGroup.onRequestSendAccessibilityEvent(view, accessibilityEvent);
    }

    @Deprecated
    public static void setMotionEventSplittingEnabled(ViewGroup viewGroup, boolean z) {
        viewGroup.setMotionEventSplittingEnabled(z);
    }

    public static int getLayoutMode(@NonNull ViewGroup viewGroup) {
        if (Build.VERSION.SDK_INT >= 18) {
            return viewGroup.getLayoutMode();
        }
        return 0;
    }

    public static void setLayoutMode(@NonNull ViewGroup viewGroup, int i) {
        if (Build.VERSION.SDK_INT >= 18) {
            viewGroup.setLayoutMode(i);
        }
    }

    public static void setTransitionGroup(@NonNull ViewGroup viewGroup, boolean z) {
        if (Build.VERSION.SDK_INT >= 21) {
            viewGroup.setTransitionGroup(z);
        } else {
            viewGroup.setTag(R.id.tag_transition_group, Boolean.valueOf(z));
        }
    }

    public static boolean isTransitionGroup(@NonNull ViewGroup viewGroup) {
        if (Build.VERSION.SDK_INT >= 21) {
            return viewGroup.isTransitionGroup();
        }
        Boolean bool = (Boolean) viewGroup.getTag(R.id.tag_transition_group);
        return ((bool == null || !bool.booleanValue()) && viewGroup.getBackground() == null && ViewCompat.getTransitionName(viewGroup) == null) ? false : true;
    }

    public static int getNestedScrollAxes(@NonNull ViewGroup viewGroup) {
        if (Build.VERSION.SDK_INT >= 21) {
            return viewGroup.getNestedScrollAxes();
        }
        if (!(viewGroup instanceof NestedScrollingParent)) {
            return 0;
        }
        return ((NestedScrollingParent) viewGroup).getNestedScrollAxes();
    }
}