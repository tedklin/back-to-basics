package design;

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * boolean param_1 = obj.enQueue(value);
 * boolean param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * boolean param_5 = obj.isEmpty();
 * boolean param_6 = obj.isFull();
 */

public class Q622_DesignCircularQueue {

    private int[] _data;

    // _head indicates the front of the queue, i.e. the next element to be dequeued
    // _tail indicates the back of the queue
    private int _head, _tail;

    public Q622_DesignCircularQueue(int k) {
        _data = new int[k];

        // Initialize to the "empty" state.
        _head = 0;
        _tail = -1;
    }

    public boolean isEmpty() {
        // The queue can only be empty
            // After it is first initialized.
            // After the back of the queue is `dequeue`d (see precond/postcond below).
                // precond: head == tail
                //          (i.e. element about to be `dequeue`d == tail)
                // postcond: head == (head+1)%k by definition
                //                == (tail+1)%k by substitution
//        return _head == ((_tail + 1) % _data.length);

        // The approach above is incorrect because it happens to be identical to our isFull condition!

        // So instead we implement the `dequeue` function to (under the precond: head == tail)
        // explicitly have the postcond:
            // tail == -1 && head == 0 (the "empty" state)
        return _tail == -1 && _head == 0;
    }

    public boolean isFull() {
        // By cases:
            // If the tail is in front of the head, then the head must be 0 and the tail must be k-1.
            // If the head is in front of the tail, then the tail must be 1 less than the head.
        // return (_tail > _head && _head == 0 && _tail == _data.length - 1)
        //         || (_head > _tail && _tail == _head - 1);

        // By mod arithmetic:
            // The tail must be k-1 ahead of the head.
        return _tail == ((_head + _data.length-1) % _data.length);
    }

    public int Front() {
        if (isEmpty()) {
            return -1;
        }
        return _data[_head];
    }

    public int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return _data[_tail];
    }

    public boolean enQueue(int value) {
        if (isFull()) {
            return false;
        }

        // By cases:
            // If the tail is at k-1, then the post-condition should be tail==0 and data[tail]==value.
            // If the tail is anywhere else, then the post-condition should be tail==old_tail+1 and data[tail]==value.
//        if (_tail == _data.length - 1) {
//            _tail = 0;
//        } else {
//            _tail++;
//        }
//        _data[_tail] = value;

        // By mod arithmetic:
        _tail = (_tail + 1) % _data.length;
        _data[_tail] = value;

        return true;
    }

    public boolean deQueue() {
        if (isEmpty()) {
            return false;
        }

        // If we're dequeueing the last element left, then reset to "empty" state.
        if (_head == _tail) {
            _head = 0;
            _tail = -1;
            return true;
        }

        // By cases:
            // If the head is at k-1, then the post-condition should be head==0.
            // If the head is anywhere else, then the post-condition should be head==old_head+1.
//        if (_head == _data.length - 1) {
//            _head = 0;
//        } else {
//            _head++;
//        }

        // By mod arithmetic:
        _head = (_head + 1) % _data.length;

        return true;
    }

}
