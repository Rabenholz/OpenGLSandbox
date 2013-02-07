#include "stdafx.h"
#include "SFMLApp.h"

void SFMLApp::OnRender(void)
{	if(m_states.size() == 0)
	{
		printf("!!! No states to render!\n");
		return;
	}
	std::vector<GameStateBase*> renderList;
	if(m_states.size() > 1 && m_states.back()->m_transparent)
	{
		for(std::vector<GameStateBase*>::reverse_iterator stateIt(m_states.rbegin()+1); stateIt != m_states.rend(); stateIt++)
		{
			if((*stateIt)->m_subRender)
				renderList.push_back(*stateIt);
			if(!(*stateIt)->m_transparent)
				break;
		}
	}
	//front state always renders on top
	renderList.push_back(m_states.back());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//printf("%d\n", glGetError());

	m_timerVal += 0.001f;
	glUseProgram(m_program1);
	glUniform1f(m_timer, m_timerVal);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(m_position1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*10, (void*)0);
	glEnableVertexAttribArray(m_position1);

	glVertexAttribPointer(m_color1, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*10, (void*)(6*sizeof(GLfloat)));
	glEnableVertexAttribArray(m_color1);

	glUniform3f(m_offset1, 2.0f, 2.0f, -5.0f);

	glDrawArrays(GL_TRIANGLES,0,36);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, (void*)0);

	glUniform3f(m_offset1, 2.0f, 1.0f, 3*std::sin(m_timerVal)-5.0f);
	glDrawArrays(GL_TRIANGLES,0,36);
	//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, (void*)0);
	
	glDisableVertexAttribArray(m_position1);
	glDisableVertexAttribArray(m_color1);
	
	m_mainWindow.display();
}

GLushort SFMLApp::squareElementArray[12] =
{
	0,1,2,3,4,5,
	6,7,6,9,10,11
};

GLfloat SFMLApp::squareVertexArray[84] =
{
	//front
	-1.0f,-1.0f,-1.0f, 1.0f,0.0f,0.0f,1.0f,
	1.0f,-1.0f,-1.0f, 1.0f,0.0f,0.0f,1.0f,
	1.0f,1.0f,-1.0f, 1.0f,0.0f,0.0f,1.0f,
	-1.0f,-1.0f,-1.0f, 1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,-1.0f, 1.0f,1.0f,0.0f,1.0f,
	-1.0f,1.0f,-1.0f, 1.0f,1.0f,0.0f,1.0f,
	//back
	-1.0f,-1.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	1.0f,-1.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	-1.0f,-1.0f,1.0f, 0.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f, 0.0f,1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f, 0.0f,1.0f,1.0f,1.0f
};


GLushort SFMLApp::cubeElementArray[36] =
{
	//0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
	0,1,2,0,1,2,0,1,2,0,1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2
};
GLfloat SFMLApp::cubeVertexArray[360] = 
{
	//x    y    z    nx   ny   nz     r    g    b    a  
	//front
	-1.0f,-1.0f,-1.0f, 0.0f,0.0f,-1.0f, 0.0f,0.0f,1.0f,1.0f,
	1.0f,-1.0f,-1.0f, 0.0f,0.0f,-1.0f, 0.0f,0.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f, 0.0f,0.0f,-1.0f, 0.0f,0.0f,1.0f,1.0f,

	-1.0f,-1.0f,-1.0f, 0.0f,0.0f,-1.0f, 1.0f,0.0f,0.0f,1.0f,
	1.0f,1.0f,-1.0f, 0.0f,0.0f,-1.0f, 1.0f,0.0f,0.0f,1.0f,
	-1.0f,1.0f,-1.0f, 0.0f,0.0f,-1.0f, 1.0f,0.0f,0.0f,1.0f,
	//back
	1.0f,-1.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	-1.0f,-1.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	-1.0f,1.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,

	1.0f,-1.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	-1.0f,1.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,1.0f, 0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,1.0f,
	//left
	-1.0f,-1.0f,1.0f, -1.0f,0.0f,0.0f, 1.0f,1.0f,0.0f,1.0f,
	-1.0f,-1.0f,-1.0f, -1.0f,0.0f,0.0f, 1.0f,1.0f,0.0f,1.0f,
	-1.0f,1.0f,-1.0f, -1.0f,0.0f,0.0f, 1.0f,1.0f,0.0f,1.0f,

	-1.0f,-1.0f,1.0f, -1.0f,0.0f,0.0f, 1.0f,1.0f,0.0f,1.0f,
	-1.0f,1.0f,-1.0f, -1.0f,0.0f,0.0f, 1.0f,1.0f,0.0f,1.0f,
	-1.0f,1.0f,1.0f, -1.0f,0.0f,0.0f, 1.0f,1.0f,0.0f,1.0f,
	//right
	1.0f,-1.0f,-1.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,1.0f,0.0f,
	1.0f,-1.0f,1.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f,1.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,1.0f,0.0f,

	1.0f,-1.0f,-1.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f,1.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f,-1.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,1.0f,0.0f,
	//bottom
	-1.0f,-1.0f,1.0f, 0.0f,-1.0f,0.0f, 0.0f,0.0f,1.0f,1.0f,
	1.0f,-1.0f,1.0f, 0.0f,-1.0f,0.0f, 0.0f,0.0f,1.0f,1.0f,
	1.0f,-1.0f,-1.0f, 0.0f,-1.0f,0.0f, 0.0f,0.0f,1.0f,1.0f,

	-1.0f,-1.0f,1.0f, 0.0f,-1.0f,0.0f, 0.0f,0.0f,1.0f,1.0f,
	1.0f,-1.0f,-1.0f, 0.0f,-1.0f,0.0f, 0.0f,0.0f,1.0f,1.0f,
	-1.0f,-1.0f,-1.0f, 0.0f,-1.0f,0.0f, 0.0f,0.0f,1.0f,1.0f,
	//top
	-1.0f,1.0f,-1.0f, 0.0f,1.0f,0.0f, 1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f, 0.0f,1.0f,0.0f, 1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f, 0.0f,1.0f,0.0f, 1.0f,1.0f,1.0f,1.0f,

	-1.0f,1.0f,-1.0f, 0.0f,1.0f,0.0f, 1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f, 0.0f,1.0f,0.0f, 1.0f,1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f, 0.0f,1.0f,0.0f, 1.0f,1.0f,1.0f,1.0f
};