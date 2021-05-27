/*
 * Student_mangement_system.h
 *
 *  Created on: May 26, 2021
 *      Author: mostafa
 */

#ifndef STUDENT_MANGEMENT_SYSTEM_H_
#define STUDENT_MANGEMENT_SYSTEM_H_


//search macros
#define first_nam			0
#define id					1
#define gpa					2
#define c_id				3
#define id_s				4
#define update_fname		5
#define update_lname		6
#define update_id			7
#define update_gpa			8
#define update_cid			9

//student database APIS
void Add_Student_Data();
void find_student_by_id();
void find_student_by_fname();
void find_student_by_course_id();
void student_count();
void Delete_student();
void update_student_data();
void print_all_students_info();
void Exit_program();



#endif /* STUDENT_MANGEMENT_SYSTEM_H_ */
