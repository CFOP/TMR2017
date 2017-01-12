#ifndef InfraredDetection_h
class InfraredDetection{
	private:
		int length;
		int* ports;
	public:
		void findBall();
		int getClosestDirection();
		int getDirection();
		
};
#endif