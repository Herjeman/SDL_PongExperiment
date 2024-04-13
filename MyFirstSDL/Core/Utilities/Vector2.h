#pragma once

struct FVector2
{
	float X;
	float Y;
	FVector2() : X(0), Y(0) {}
	FVector2(float x, float y) : X(x), Y(y) {}

	FVector2 operator+ (const FVector2& vec)
	{
		FVector2 out;
		out.X = this->X + vec.X;
		out.Y = this->Y + vec.Y;
		return out;
	}

	FVector2 operator* (const float& factor)
	{
		FVector2 out;
		out.X = X * factor;
		out.Y = Y * factor;
		return out;
	}
};

