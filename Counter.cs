public class Counter
{
    private int _value;
    private int _ticks;

    public void Increment()
    {
        _value++;
    }

    public void Decrement()
    {
        if (_value > 0)
            _value--;
    }

    public void Reset()
    {
        _value = 0;
        _ticks = 0;
    }

    public void Tick()
    {
        _ticks++;
    }

    public int GetValue()
    {
        return _value;
    }

    public int GetTicks()
    {
        return _ticks;
    }

    public bool IsZero()
    {
        return _value == 0;
    }
}