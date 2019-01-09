using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreUpdater : MonoBehaviour {

    public Text scoreLabel;
    public string scoreText = "Score: {0}";



    // Update is called once per frame
    void Update()
    {
        uint currentScore = 0;
        var gameStateController = GameStateController.Instance;
        if (gameStateController)
        {
            currentScore = gameStateController.GetCurrentScore();
        }
        scoreLabel.text = string.Format(scoreText, currentScore);
    }
}
