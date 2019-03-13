Reinforcement Learning Assignment

---First Visit MC Prediction---
Policy: pi

V(s) = array of integers
Returns = array for each state = 2d array of integers

x = arbitrary number 
Loop x times:
    -generate_episode(pi) -> returns an array of tuples? of state-action-reward pairs all the way to the terminal step T, (include total return RT?)
    -init G = 0
    Loop BACKWARDS from T-1 to 0:
        G = gamma(G) + Rt+1 //first iteration: get reward for moving to terminal state
        if St is in generated_episode:
            Returns[St].append(G)
            V(St) = average(Returns[St])

git commit -m "message"
git push -u origin mybranch
