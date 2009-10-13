-module(pi).
-export([circle_pi/1, leibniz_pi/1, main/0]).

%% We're using a unit circle for all the calculations here.
-define(radius, 1.0).

%% Just to help get the height of a right-angle triangle.
height(Base, Hypotenuse) when Base*Base =< Hypotenuse * Hypotenuse ->
	math:sqrt(Hypotenuse*Hypotenuse - Base*Base);
height(_, _) ->
	0.

%% Calculates pi by approximating it via the area of a circle formula.
circle_pi(Rectangles) ->
	circle_pi(?radius/Rectangles, 0.0, 0.0).

circle_pi(Width, Length, Sum) when Length < 1 ->
	circle_pi(Width, Length+Width, Sum + Width*height(Width/2 + Length, ?radius));
circle_pi(_, _, Sum) ->
	4*Sum.

%% Approximates pi using Leibniz's method.
leibniz_pi(Iterations) ->
	leibniz_pi(Iterations, 1, 0).

leibniz_pi(Iterations, Denominator, Sum) when Denominator < (Iterations*2) ->
	case ((Denominator div 2) rem 2) of
		0 -> leibniz_pi(Iterations, Denominator+2, Sum + 1/Denominator);
		1 -> leibniz_pi(Iterations, Denominator+2, Sum - 1/Denominator)
	end;
leibniz_pi(_, _, Sum) ->
	4*Sum.

%% Prints out all the values of pi calculated nicely.
print_values() ->
	print_values(1).

print_values(Current) when Current =< 1000000 ->
	io:format("~10B~20.12f~16.12f~n", [Current, circle_pi(Current), leibniz_pi(Current)]),
	print_values(Current*10);
print_values(_) ->
	ok.

main() ->
	io:format("Approximations for pi~n"),
	io:format("Iterations      Circle Method   Leibniz Method~n"),
	io:format("----------------------------------------------~n"),
	print_values().

