#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
	double x;
	double y;
	double z;
} Vector;

void print_vector(const Vector v);
Vector sum(const Vector v1, const Vector v2);
Vector diff(const Vector v1, const Vector v2);
Vector multiplyby_scalar(const Vector v1, const double c);
double dot_product(const Vector v1, const Vector v2);
Vector cross_product(const Vector v1, const Vector v2);
double norm(const Vector v);
int is_unitvector(const Vector v);
Vector unit(const Vector v);
double angle(const Vector v1, const Vector v2);
double distance(const Vector v1, const Vector v2);
int are_linearly_independent(const Vector v1, const Vector v2, const Vector v3);
int are_orthogonal(const Vector v1, const Vector v2, const Vector v3);
int are_orthonormal(const Vector v1, const Vector v2, const Vector v3);
Vector projection(const Vector v1, const Vector v2);
int convert_2_orthogonal_basis(Vector *v1, Vector *v2, Vector *v3);
char* vector2str(const Vector v);


int main () 
{
	Vector v1 = {1, 2, 2}, v2 = {-1, 0, 2}, v3 = {0, 0, 1};
	double k = 2;

	printf("v1 = ");
    print_vector(v1);
    printf("v2 = ");
    print_vector(v2);
    printf("v3 = ");
    print_vector(v3);
    
    printf("v1 + v2 = ");
	print_vector(sum(v1, v2));
	
	printf("v1 - v2 = ");
	print_vector(diff(v1, v2));
	
	printf("k * v1  = ");
	print_vector(multiplyby_scalar(v1, k));
    
    printf("v1 . v2 = %.2lf\n", dot_product(v1, v2));
    
    printf("v1 x v2 = ");
	print_vector(cross_product(v1, v2));
	
	printf("| v1 |  = %.2lf\n", norm(v1));
	
	if(is_unitvector(v1))
		printf("v1 is a unit vector.\n");
	else
		printf("v1 is not unit vector.\n");
		
	printf("unit( v1 ) = ");
	print_vector(unit(v1));	
	
	printf("angle(v1, v2) = %.2lf\n", angle(v1, v2));
	
	printf("distance(v1, v2) = %.2lf\n", distance(v1, v2));
	
	if(are_linearly_independent(v1, v2, v3))
		printf("Vectors are linearly independent.\n");
	else
		printf("Vectors are not linearly independent.\n");
		
	if(are_orthogonal(v1, v2, v3))
		printf("Vectors are orthogonal.\n");
	else
		printf("Vectors are not orthogonal.\n");	
	
	if(are_orthonormal(v1, v2, v3))
		printf("Vectors are orthonormal.\n");
	else
		printf("Vectors are not orthonormal.\n");
	
	printf("Projection of v1 onto v2 is = ");
	print_vector(projection(v1, v2));
	
	if(convert_2_orthogonal_basis(&v1, &v2, &v3)){
		printf("Orthogonalization of vectors:\n");
		printf("v1 = ");
	    print_vector(v1);
	    printf("v2 = ");
	    print_vector(v2);
	    printf("v3 = ");
	    print_vector(v3);
	}		
    
    puts(vector2str(v1));		
    
    return 0;  
}

void print_vector(const Vector v){
	
	printf("{%.2f, %.2f, %.2f}\n",v.x,v.y,v.z);
}

Vector sum(const Vector v1, const Vector v2){
	
	Vector V;
	
	V.x = v1.x + v2.x;
	V.y = v1.y + v2.y;
	V.z = v1.z + v2.z;
	
	return V;
}

Vector diff(const Vector v1, const Vector v2){
	
	Vector V;
	
	V.x = v1.x - v2.x;
	V.y = v1.y - v2.y;
	V.z = v1.z - v2.z;
	
	return V;
}

Vector multiplyby_scalar(const Vector v1, const double c){
	
	Vector V;
	
	V.x = c * v1.x;
	V.y = c * v1.y;
	V.z = c * v1.z;
	
	return V;
}

double dot_product(const Vector v1, const Vector v2){
	
	double dotproduct;
	
	dotproduct = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z ;
	
	return dotproduct;
}

Vector cross_product(const Vector v1, const Vector v2){
	
	Vector V;
	
	V.x = (v1.y * v2.z)-(v1.z * v2.y);
	V.y = (v1.z * v2.x)-(v1.x * v2.z);
	V.z = (v1.x * v2.y)-(v1.y * v2.x);
	
	return V;
}

double norm(const Vector v){
	double norm;

	norm = sqrt (pow(v.x,2) + pow(v.y,2) + pow(v.z,2));
	
	return norm;
}

int is_unitvector(const Vector v){
	
	double norm1;
	norm1 = norm(v);
	
	if(norm1 == 1){
		return 1;
	}
	else{
		return 0;
	}
}

Vector unit(const Vector v){
	
	double norm1;
	Vector Unit;

	norm1 = norm(v);
	
	Unit.x = v.x / norm1 ;
	Unit.y = v.y / norm1 ;
	Unit.z = v.z / norm1 ;
	
	return Unit;
}

double angle(const Vector v1, const Vector v2){
	
	const double PI =  3.1415926;
	double angle,norm1,norm2;
	norm1 = norm(v1);
	norm2 = norm(v2);
	double dotproduct = dot_product(v1, v2);
	
	angle = (acos((dotproduct)/(norm1*norm2))*180)/PI;
	
	return angle;
}

double distance(const Vector v1, const Vector v2){
	
	double distance;
	Vector V;
	
	V.x = v1.x - v2.x ;
	V.y = v1.y - v2.y ;
	V.z = v1.z - v2.z ;
	
	distance = norm(V);
	
	return distance;
}

int are_linearly_independent(const Vector v1, const Vector v2, const Vector v3){

	int determinant;
	
	determinant = v1.x * ((v2.y*v3.z)-(v3.y*v2.z)) - v2.x * ((v1.y*v3.z)-(v3.y*v1.z)) - v3.x * ((v1.y*v2.z)-(v2.y*v1.z)) ;
	
	if(determinant != 0){
		return 1;
	}
	else{
		return 0;
	}
}

int are_orthogonal(const Vector v1, const Vector v2, const Vector v3){
	
	if(dot_product(v1, v2)==0 && dot_product(v1, v3)==0 && dot_product(v2, v3)==0){
		return 1;
	}
	else{
		return 0;
	}
}

int are_orthonormal(const Vector v1, const Vector v2, const Vector v3){
	
	if(dot_product(v1, v2)==0 && dot_product(v1, v3)==0 && dot_product(v2, v3)==0){
		return 1;
	}
	else{
		return 0;
	}
}

Vector projection(const Vector v1, const Vector v2){
	 
	double k;
	Vector V;
	 
	k = dot_product(v1,v2)/pow(norm(v2),2);
	 
	V.x = v2.x * k;
	V.y = v2.y * k;
	V.z = v2.z * k;
	 
	return V;
}

int convert_2_orthogonal_basis(Vector *v1, Vector *v2, Vector *v3){
	
	Vector a,b,c;
	 
	b.x = v2->x ; 
	b.y = v2->y ; 
	b.z = v2->z ; 
	c.x = v3->x ; 
	c.y = v3->y ; 
	c.z = v3->z ; 
	 	
	if(are_linearly_independent(*v1, *v2, *v3)){
		
		v2->x = v2->x - projection(b,*v1).x ;	
		v2->y = v2->y - projection(b,*v1).y ;	
		v2->z = v2->z - projection(b,*v1).z ;
		v3->x = c.x - projection(c,*v1).x - projection(c,*v2).x ;	
		v3->y = c.y - projection(c,*v1).y - projection(c,*v2).y ;
		v3->z = c.z - projection(c,*v1).z - projection(c,*v2).z ;
		
		return 1;	
	}
	else{
		printf("these vectors are not linearly independent");
		
		return 0;
	}
}

char* vector2str(const Vector v){
	
	char *str ;
	
	str = (char *)malloc(sizeof(int)*10);	
	
	sprintf(str,"(%.2f,%.2f,%.2f)",v.x,v.y,v.z);	
		
	return str;
}












