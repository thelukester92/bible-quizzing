
# States

* score:		Displaying score.
* question:		Displaying question.
* answering:	Waiting on player to answer.
* bonus:		Displaying bonus question.
* substitute:	Selecting a player to switch out.
* timeout:		Taking a timeout.

# Transitions

* next:			Quiz master chooses to continue.
* sub:			A team substitutes one of its players.
* time:			A team uses a timeout.
* buzz:			A player buzzes in, quiz master inputs the player team and seat number.
* correct:		A player answers correctly.
* incorrect:	A player answers incorrectly or runs out of time.

# Transition Table

| State      | Transition | Next State |
|------------|------------|------------|
| score      | next       | question   |
| score      | sub        | substitute |
| score      | time       | timeout    |
| question   | buzz       | answering  |
| answering  | correct    | score      |
| answering  | incorrect  | bonus      |
| bonus      | correct    | score      |
| bonus      | incorrect  | score      |
| substitute | next       | score      |
| timeout    | next       | score      |

# main

	Quiz quiz = createQuiz()
	int state = STATE_SCORE
	int questionNumber = 0
	
	int team, seat
	
	while state != STATE_END
	{
		switch state
		{
			case STATE_SCORE:
				displayScore()
				
				if questionNumber < quiz.getQuestionCount()
				{
					switch getInput()
					{
						case SUBSTITUTE:
							state = STATE_SUBSTITUTE
							break
						
						case TIMEOUT:
							state = STATE_TIMEOUT
							break
						
						case QUESTION:
							state = STATE_QUESTION
							break
					}
				}
				else
				{
					state = STATE_END
				}
				
				break
			
			case STATE_QUESTION:
				displayQuestion(quiz.getQuestion(questionNumber++))
				
				(team, seat) = getPlayerWhoBuzzedIn()
				state = STATE_ANSWERING
				
				break
			
			case STATE_ANSWERING:
				startTimer()
				
				if getAnswer() == ANSWER_CORRECT
				{
					quiz.answerCorrectly(team, seat)
					state = STATE_SCORE
				}
				else
				{
					quiz.answerIncorrectly(team, seat)
					state = STATE_BONUS
				}
				
				break
			
			case STATE_BONUS:
				displayQuestion(quiz.getBonusQuestion())
				
				startTimer()
				
				if getAnswer() == ANSWER_CORRECT
				{
					quiz.answerBonusCorrectly(team, seat)
				}
				else
				{
					quiz.answerBonusIncorrectly(team, seat)
				}
				
				state = STATE_SCORE
				
				break
			
			case STATE_SUBSTITUTE:
				(team, seat) = getPlayerToSubstitute()
				quiz.substitute( team, seat, getNewPlayerId() )
				state = STATE_SCORE
				break
			
			case STATE_TIMEOUT:
				quiz.timeout( getTimeoutTeam() );
				break
		}
	}
	
