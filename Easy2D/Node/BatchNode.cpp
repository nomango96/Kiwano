#include "..\easy2d.h"
#include "..\EasyX\easyx.h"
#include <assert.h>

BatchNode::BatchNode()
{
}


BatchNode::~BatchNode()
{
	clearAllChildren();
}

bool BatchNode::_exec(bool active)
{
	// �����ڵ��Ƿ���ʾ
	if (!m_bDisplay)
	{
		return false;
	}
	// ������������ӽڵ�
	for (int i = int(m_vChildren.size() - 1); i >= 0; i--)
	{
		assert(m_vChildren[i]);
		if (m_vChildren[i]->_exec(active))
		{
			active = false;
		}
	}
	// ���ӽڵ�ȡ���˻��潹�㣬��ýڵ�Ҳȡ���˽���
	return !active;
}

void BatchNode::_onDraw()
{
	// �ڵ��Ƿ���ʾ
	if (!m_bDisplay)
	{
		return;
	}
	
	// �����λ�û����ӽڵ�
	App::setOrigin(App::getOriginX() + m_nX, App::getOriginY() + m_nY);
	for (auto child : m_vChildren)
	{
		assert(child);
		child->_onDraw();
	}
	App::setOrigin(App::getOriginX() - m_nX, App::getOriginY() - m_nY);
}

void BatchNode::add(Node * child, int z_Order)
{
	// �������ӵĽڵ�ǿ�
	assert(child);
	// ���ýڵ�ĸ�����
	child->setParentScene(this->getParentScene());
	// ���ýڵ��������ڵ��е� z ��˳��
	child->setZOrder(z_Order);
	// ��������ü�����һ
	child->retain();

	// �� z ��˳�����ڵ�
	size_t size = m_vChildren.size();
	for (unsigned i = 0; i <= size; i++)
	{
		if (i != size)
		{
			if (z_Order < m_vChildren.at(i)->getZOrder())
			{
				m_vChildren.insert(m_vChildren.begin() + i, child);
				break;
			}
		}
		else
		{
			m_vChildren.push_back(child);
			break;
		}
	}
}

bool BatchNode::del(Node * child)
{
	// ���Խڵ�ǿ�
	assert(child);

	// Ѱ���Ƿ�����ͬ�ڵ�
	std::vector<Node*>::iterator iter;
	for (iter = m_vChildren.begin(); iter != m_vChildren.end(); iter++)
	{
		// �ҵ���ͬ�ڵ�
		if ((*iter) == child)
		{
			// ��������ü�����һ
			(*iter)->release();
			// ȥ���ýڵ�
			m_vChildren.erase(iter);
			return true;
		}
	}
	return false;
}

void BatchNode::clearAllChildren()
{
	// ���нڵ�����ü�����һ
	for (auto child : m_vChildren)
	{
		child->release();
	}
	// ��մ���ڵ������
	m_vChildren.clear();
}