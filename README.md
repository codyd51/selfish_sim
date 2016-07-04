Selfish Sim
--------------------

Inspired by [this video](https://www.youtube.com/watch?v=BOvAbjfJ0x0), this is a simulator to rank various cooperation strategies.

Every strategy is matched against every other strategy and the pair play through the [Prisoner's Dilemna](https://en.wikipedia.org/wiki/Prisoner%27s_dilemma) 200 times per matching. Instead of receiving a prison sentence, players are assigned arbitrary 'points' based on the outcome of the game. 

Once all matchings have been made and have played through their game set, players are ranked based on their average scores.

The points in this scenario could be used to model things such as precious resources. If we consider the 'points' as a scarce resource such as food or money, the most competent strategies would therefore be the most biologically fit, and would move on to the next generation.

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

As each matchup contains 200 games, there is a bounded range of possible scores that can be acheived per matchup. If we consider the best case for our opponent, a player that always cooperates and never retaliates if we defect against them (modeled in the Samaritan strategy), then we can exploit them by always defecting every turn (as the Villain strategy does). In this matchup, Villain would receive 1000 points, and Samaritan would receive 0, the respective best and worst possible scores per matchup. Average scores should be read within the context of this score range.

A typical tournament might result in something like this:



GPL v3 license
