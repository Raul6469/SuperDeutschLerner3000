#include "TrainingSession.h"

#include <algorithm>
#include <random>
#include <chrono>

TrainingSession::TrainingSession (Lesson lesson) : m_lesson (lesson)
{
	DictionnaryType dict = m_lesson.getDictionnary ();
	int size = m_lesson.getDictionnary ().size ();
	int *indexes = new int[dict.size ()];
	for (int i = 0; i < size; i++)
	{
		indexes[i] = i;
	}
	unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
	std::shuffle (&indexes[0], &indexes[size], std::default_random_engine (seed));
	for (int i = 0; i < size; i++)
	{
		unansweredTuples.push_back (dict[indexes[i]]);
	}
}

QString TrainingSession::getNext ()
{
	bool askTranslation = rand () % 2;

	tupleAsked = { unansweredTuples.front (), askTranslation };
	unansweredTuples.pop_front ();

	if (askTranslation)
		return tupleAsked.first.getOriginal ();
	return tupleAsked.first.getTranslated ();
}

QPair<Tuple, bool > TrainingSession::answer (QString givenAnswer)
{
	QString stringAsked;

	if (tupleAsked.second)
		stringAsked = tupleAsked.first.getTranslated ();
	else
		stringAsked = tupleAsked.first.getOriginal ();

	answeredTuples.push_back ({ tupleAsked.first, stringAsked == givenAnswer });

	return answeredTuples.back();
}

int TrainingSession::getRemaining ()
{
	return unansweredTuples.size ();
}

int TrainingSession::getCorrectAnswers ()
{
	int correctCount = 0;
	for (auto it : answeredTuples)
		correctCount += it.second;
	return correctCount;
}

int TrainingSession::getTotalAnswers ()
{
	return answeredTuples.size ();
}

bool TrainingSession::isOver ()
{
	return getRemaining() == 0;
}