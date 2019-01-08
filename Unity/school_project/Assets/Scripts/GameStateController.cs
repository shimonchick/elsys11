using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameStateController : MonoBehaviour {

    public float GameOverScreenDelay = 2.0f;
    public float WinScreenDelay = 2.0f;
    public string GameOverScene = "GameOver";
    public string AsteroidScene = "Main";
    public string BossBattleScene = "BossBattle";
    public string WinScene = "WinScene";
    private uint CurrentScore = 0;
    public uint CurrentAsteroids = 0;
    public static GameStateController Instance { get; private set; }

    
    private List<Vector4> playerPositionAtTime; // I could not find a generic hash table
    private GameObject player;
    void Awake()
    {
        if (Instance == null)
        {
            Instance = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            Destroy(gameObject);
        }
    }
    private void Start()
    {
        player = FindObjectOfType<PlayerController>().gameObject;
        playerPositionAtTime = new List<Vector4>();
    }

    public void AddPlayerPosition(Vector3 position)
    {
        Vector4 positionAtTime = new Vector4(position.x, position.y, position.z, Time.time);
        playerPositionAtTime.Add(positionAtTime);
    }
    public Vector3 GetPositionAtTime(float time)
    {
        for(int i = 0; i < playerPositionAtTime.Count; i++)
        {
            if(playerPositionAtTime[i].w - time <= Time.deltaTime)
            {
                Vector3 result = new Vector3(playerPositionAtTime[i].x, playerPositionAtTime[i].y, playerPositionAtTime[i].z);
                return result;
            }
        }
        throw new System.Exception();
    }



    public void OnPlayerSpawned()
	{
		CurrentScore = 0;
	}

	public void OnPlayerDied()
	{
		Invoke ("ShowGameOverScreen", GameOverScreenDelay);
	}

    public void OnBossDied()
    {
        //might load other scenes in the future
        OnPlayerWin();
    }
    public void OnPlayerWin()
    {
        Invoke("ShowWinScreen", WinScreenDelay);
    }

	public void IncrementScore(uint scoreToAdd)
	{
		CurrentScore += scoreToAdd;
	}
	public uint GetCurrentScore()
	{
		return CurrentScore;
	}


	void ShowGameOverScreen()
	{
		SceneManager.LoadScene (GameOverScene);
	}
    void ShowWinScreen()
    {
        SceneManager.LoadScene(WinScene);
    }

    private void Update()
    {
        if (!player) return;
        AddPlayerPosition(player.transform.position);
        if (CurrentAsteroids == 0 && SceneManager.GetActiveScene().name == AsteroidScene)
        {
            //Debug.Log("Boss battle");
            SceneManager.LoadScene(BossBattleScene);
        }
        
    }

}
