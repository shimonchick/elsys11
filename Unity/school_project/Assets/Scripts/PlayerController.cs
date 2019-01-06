using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerController : MonoBehaviour
{
    public float PlayerSpeed = 0.2f;

    [SerializeField]
    private float changeMaterialTime = 2.0f;
	//public string GameOverScene = "GameOver";

    [SerializeField]
    private List<Spell> spells;

    void Start()
    {
        if (AsteroidSpawner.Instance)
        {
            AsteroidSpawner.Instance.RegisterPlayer(gameObject);
        }
		GameStateController.Instance.OnPlayerSpawned ();
    }

    //void OnDestroy()
    //{
    //    AsteroidSpawner.Instance.UnregisterPlayer(gameObject);
	//	GameStateController.Instance.OnPlayerDied ();
    //}

    void FixedUpdate()
    {
        MoveShipWithPhysics();
    }

    void Update()
    {
        UpdateShootInputs();
    }

    private void UpdateShootInputs()
    {
        if (Input.GetButton("Fire1"))
        {
            GetComponent<Weapon>().Shoot();
        }
    }


    private void MoveShipWithPhysics()
    {
        float verticalInput = Input.GetAxis("Vertical");
        float horizontalInput = Input.GetAxis("Horizontal");
        float playerCameraOffset = Camera.main.transform.position.y - transform.position.y;
        Vector3 mousePositionScreenSpace = new Vector3(Input.mousePosition.x, Input.mousePosition.y, playerCameraOffset);
        Vector3 mousePositionWorldSpace = Camera.main.ScreenToWorldPoint(mousePositionScreenSpace);

        Quaternion newRotation = Quaternion.LookRotation(mousePositionWorldSpace - transform.position);
        Vector3 direction = new Vector3(horizontalInput, 0, verticalInput);
        //direction = transform.rotation * direction;
        direction = direction * PlayerSpeed * Time.deltaTime;

        Rigidbody rb = GetComponent<Rigidbody>();
        rb.MovePosition(transform.position + direction);
        rb.MoveRotation(newRotation);
    }

    public void CastSpell(int index)
    {
        if (index > spells.Count)
        {
            return;
        }
        spells[index].Cast();
        UIManager.Instance.Cooldown(spells[index].Cooldown, index);
    }

    public void ChangeMaterial(Material material)
    {
        StartCoroutine(ChangeMaterial(material, changeMaterialTime));
    }

    public IEnumerator ChangeMaterial(Material material, float changeMaterialTime)
    {
        Debug.Log("changing material");
        Material oldMaterial = GetComponent<MeshRenderer>().material;
        yield return  new WaitForSeconds(changeMaterialTime);
        GetComponent<MeshRenderer>().material = oldMaterial;
    }
}