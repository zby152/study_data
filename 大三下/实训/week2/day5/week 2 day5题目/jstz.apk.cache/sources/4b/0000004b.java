package android.arch.lifecycle;

import android.arch.core.util.Function;
import android.support.annotation.MainThread;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

/* loaded from: classes.dex */
public class Transformations {
    private Transformations() {
    }

    @MainThread
    public static <X, Y> LiveData<Y> map(@NonNull LiveData<X> liveData, @NonNull final Function<X, Y> function) {
        final MediatorLiveData mediatorLiveData = new MediatorLiveData();
        mediatorLiveData.addSource(liveData, new Observer<X>() { // from class: android.arch.lifecycle.Transformations.1
            @Override // android.arch.lifecycle.Observer
            public void onChanged(@Nullable X x) {
                MediatorLiveData.this.setValue(function.apply(x));
            }
        });
        return mediatorLiveData;
    }

    @MainThread
    public static <X, Y> LiveData<Y> switchMap(@NonNull LiveData<X> liveData, @NonNull final Function<X, LiveData<Y>> function) {
        final MediatorLiveData mediatorLiveData = new MediatorLiveData();
        mediatorLiveData.addSource(liveData, new Observer<X>() { // from class: android.arch.lifecycle.Transformations.2
            LiveData<Y> mSource;

            @Override // android.arch.lifecycle.Observer
            public void onChanged(@Nullable X x) {
                LiveData<Y> liveData2 = (LiveData) Function.this.apply(x);
                Object obj = this.mSource;
                if (obj == liveData2) {
                    return;
                }
                if (obj != null) {
                    mediatorLiveData.removeSource(obj);
                }
                this.mSource = liveData2;
                Object obj2 = this.mSource;
                if (obj2 == null) {
                    return;
                }
                mediatorLiveData.addSource(obj2, new Observer<Y>() { // from class: android.arch.lifecycle.Transformations.2.1
                    @Override // android.arch.lifecycle.Observer
                    public void onChanged(@Nullable Y y) {
                        mediatorLiveData.setValue(y);
                    }
                });
            }
        });
        return mediatorLiveData;
    }
}