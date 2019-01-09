using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class UIManager : MonoBehaviour
{

    [SerializeField] private Image[] cooldownMask;

    [SerializeField] private Text scoreLabel;
    [SerializeField] private string scoreText = "Score: {0}";


    //private Stat playerHealthBar;
    //private Stat enemyHealthBar;

    public static UIManager Instance { get; private set; }

    void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            //DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }

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




    public IEnumerator Cooldown(float time, int index)
    {
        Debug.Log("cooldown on spell with time:" + time + " and index:" + index);
        cooldownMask[index].enabled = true;

        float currentCooldown = time;
        while (currentCooldown >= 0)
        {
            cooldownMask[index].fillAmount = currentCooldown / time;
            currentCooldown -= Time.deltaTime;
            yield return new WaitForEndOfFrame();
        }
        cooldownMask[index].enabled = false;
    }

}