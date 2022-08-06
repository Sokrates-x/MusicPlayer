#ifndef MOVE_ONLY_FUNCTION_H
#define MOVE_ONLY_FUNCTION_H 1

template <typename R, typename... Args> 
class MoveOnlyFunction {
public:
	typedef R result_type; 
	MoveOnlyFunction();	
};

template <typename R, typename... Args> 
MoveOnlyFunction<R(Args...)>::MoveOnlyFuntion<R(Args...)() {}

#endif // MOVE_ONLY_FUNCTION_H
