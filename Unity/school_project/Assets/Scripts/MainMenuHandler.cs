using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MainMenuHandler : MonoBehaviour {

    public string PVEGame = "Main";
    public string PVAiGame = "BossBattle";


    public void loadPVE()
    {
        SceneManager.LoadScene(PVEGame);
    }
    public void loadPvAI()
    {
        SceneManager.LoadScene(PVAiGame);
    }
}
