enum class pulsingCodes
{
    Fast,
    Normal,
    Slow,
};
class pulsing
{
private:
    /* data */
public:
    pulsing(/* args */);
    ~pulsing();
    int applyPulsing(pulsingCodes pCodes);
};
