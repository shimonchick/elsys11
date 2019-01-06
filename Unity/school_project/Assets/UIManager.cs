using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class UIManager : MonoBehaviour
{
    [SerializeField] private Button[] buttons;
    private KeyCode spell1, spell2, spell3, spell4;
    private int buttonIndex;

    [SerializeField] private Image[] cooldownMask;
    [SerializeField] private GameObject targetFrame;

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

    void Start()
    {
        spell1 = KeyCode.Alpha1;
        spell2 = KeyCode.Alpha2;
        spell3 = KeyCode.Alpha3;
        spell4 = KeyCode.Alpha4;

    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(spell1))
        {
            SpellButtonOnClick(0);
        }
        if (Input.GetKeyDown(spell2))
        {
            SpellButtonOnClick(1);
        }
        if (Input.GetKeyDown(spell3))
        {
            SpellButtonOnClick(2);
        }
        if (Input.GetKeyDown(spell4))
        {
            SpellButtonOnClick(3);
        }

    }

    private void SpellButtonOnClick(int buttonIndex)
    {
        Debug.Log("Spell clicked");
        buttons[buttonIndex].onClick.Invoke();
 
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