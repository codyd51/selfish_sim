Selfish Sim
--------------------

Inspired by [this video](#https://www.youtube.com/watch?v=BOvAbjfJ0x0), this is a simulator to rank various cooperation strategies.

Every strategy is matched against every other strategy and the pair play through the [Prisoner's Dilemna](#https://en.wikipedia.org/wiki/Prisoner%27s_dilemma) 200 times per matching. Instead of receiving a prison sentence, players are assigned arbitrary 'points' based on the outcome of the game. 

Once all matchings have been made and have played through their game set, players are ranked based on their average scores.

The points in this scenario could be used to model things such as precious resources. If we consider the 'points' as a scare resource such as food or money, the most competent strategies would therefore be the most biologically fit, and would move on to the next generation.

Currently, we model these strategies:

| Name               | Description |
| ------------------ | -----------:|
| Samaritan          | Always cooperates |
| Villain            | Always defects |
| Random             | Randomly cooperates or defects |
| Fickle             | Alternates between cooperating and defecting |
| Grudger            | Cooperates, but if the opponent ever defects it never cooperates again |
| Tit for Tat        | Repeats whatever the opponent did last move |
| Joss               | Like Tit for Tat, but randomly defects sometimes |
| Forgiving Tit for Tat | Like Tit for Tat, but requires 2 consecutive defections until it retaliates |

GPL v3 license
