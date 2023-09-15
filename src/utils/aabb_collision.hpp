bool checkAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH)
{
    return (aX < bX + bW && aX + aW > bX && aY < bY + bH && aY + aH > bY);
}
